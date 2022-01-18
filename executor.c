/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:41:40 by weng              #+#    #+#             */
/*   Updated: 2022/01/18 14:05:57 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fork the current process and returns the pid. Raises error upon failure. */
static pid_t	ft_fork(void)
{
	pid_t			pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

/*
Close unnecessary file descriptors. Parent process will save the write
end of the pipe to a static variable fd_in.
*/
static void	ft_fd_cleanup(pid_t pid, int *fd_in, int fd_pipe[2], int nofork)
{
	if (nofork == 1)
	{
		if (*fd_in != -1)
			ft_pipe_dup_close(*fd_in, STDIN_FILENO);
		*fd_in = fd_pipe[0];
		if (fd_pipe[1] != -1)
			ft_pipe_dup_close(fd_pipe[1], STDOUT_FILENO);
	}
	else if (pid == 0)
	{
		if (*fd_in != -1)
			ft_pipe_dup_close(*fd_in, STDIN_FILENO);
		if (fd_pipe[0] != -1)
			ft_close(fd_pipe[0]);
		if (fd_pipe[1] != -1)
			ft_pipe_dup_close(fd_pipe[1], STDOUT_FILENO);
	}
	else
	{
		if (*fd_in != -1)
			ft_close(*fd_in);
		*fd_in = fd_pipe[0];
		if (fd_pipe[1] != -1)
			ft_close(fd_pipe[1]);
	}
}

/*
Execute the i-th simple command by forking. After the fork, the
child process will execute a program while the parent process will
return the pid of the child process. A pipe will be created between
process i and process i+1, only if 'islast' is equal to 0.

If there is only 1 command, and it is a built-in function, no forking
will occur. The parent process will execute the built-in function, and
return 0.
*/
pid_t	ft_execute_scmd(t_scmd *scmd, int sibling, int islast)
{
	static int	fd_in = -1;
	int			fd_pipe[2];
	int			nofork;
	pid_t		pid;

	fd_in = ft_open_infile(scmd, fd_in);
	if (fd_in == -1 && scmd->infile != NULL)
		return (-1);
	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
	if (islast == 0)
		ft_pipe_create(fd_pipe);
	fd_pipe[1] = ft_open_outfile(scmd, fd_pipe[1]);
	if (fd_pipe[1] == -1 && scmd->outfile != NULL)
		return (-1);
	nofork = (sibling == 0 && ft_builtin(scmd->argv->content) != NULL);
	pid = 0;
	if (nofork != 1)
		pid = ft_fork();
	ft_fd_cleanup(pid, &fd_in, fd_pipe, nofork);
	if (pid == 0)
		ft_run(scmd->argv, nofork);
	return (pid);
}

/* Put the non-zero pid into a linked list */
static void	ft_record_pid(t_list **lst, pid_t pid)
{
	int	*ptr;

	if (pid == 0)
		return ;
	ptr = malloc(sizeof(int));
	if (ptr != NULL)
		*ptr = pid;
	ft_lstadd_back(lst, ft_lstnew(ptr));
}

/* Execute a command / pipeline and return the exit value. */
int	ft_execute_cmd(t_cmd *cmd)
{
	t_list	*lst;
	int		i;
	int		retval;

	if (cmd == NULL)
	{
		ft_putenv("?=1");
		return (EXIT_FAILURE);
	}
	lst = NULL;
	ft_signal(SIGINT, SIG_IGN);
	ft_save_restore_fd();
	i = -1;
	while (++i < cmd->count)
		ft_record_pid(&lst, ft_execute_scmd(ft_lstget(cmd->scmd, i)->content,
				cmd->count - 1, i == cmd->count - 1));
	retval = ft_set_exit_value(lst);
	if (retval == 130)
		ft_new_prompt_line(NULL);
	else if (retval == 131)
		ft_new_prompt_line("Quit");
	ft_lstclear(&lst, free);
	ft_save_restore_fd();
	ft_sighandler_shell();
	return (retval);
}

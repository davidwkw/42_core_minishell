/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:41:40 by weng              #+#    #+#             */
/*   Updated: 2022/01/04 14:54:58 by weng             ###   ########.fr       */
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
Execute the i-th command in the t_cmd by forking. After the fork, the
child process will execute a program while the parent process will
return the pid of the child process.

If there is only 1 command, and it is a built-in function, no forking
will occur. The parent process will execute the built-in function, and
return 0.
*/
pid_t	ft_execute_scmd(t_cmd *cmd, int i)
{
	static int	fd_in = -1;
	int			fd_pipe[2];
	char		**args;
	int			nofork;
	pid_t		pid;

	if (fd_in == -1 && cmd->infile != NULL)
		fd_in = open_infile(cmd);
	if (fd_in == -1 && cmd->infile != NULL)
		return (-1);
	fd_pipe[0] = -1;
	if (i < cmd->count - 1)
		ft_pipe_create(fd_pipe);
	else
		fd_pipe[1] = open_outfile(cmd);
	args = ft_scmd_to_arr(cmd->scmd_lst->content);
	nofork = (cmd->count == 1 && ft_builtin(args[0]) != NULL);
	pid = 0;
	if (nofork != 1)
		pid = ft_fork();
	ft_fd_cleanup(pid, &fd_in, fd_pipe, nofork);
	if (pid == 0)
		ft_run(args, nofork);
	ft_memdel(args);
	return (pid);
}
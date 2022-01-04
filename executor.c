/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:41:40 by weng              #+#    #+#             */
/*   Updated: 2022/01/03 23:06:58 by weng             ###   ########.fr       */
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
static void	ft_fd_cleanup(pid_t pid, int *fd_in, int fd_pipe[2])
{
	if (pid == 0)
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

/* Execute an external program, or raises error if program is not found. */
static void	ft_exec_external(char **args)
{
	char		**dirs;
	char		*pathname;
	int			i;

	dirs = ft_split(ft_getenv("PATH"), ':');
	i = -1;
	while (dirs[++i] != NULL)
	{
		pathname = ft_strjoin(dirs[i], "/");
		pathname = ft_strappend(pathname, args[0]);
		if (access(pathname, F_OK) == 0)
			execve(pathname, args, NULL);
		free(pathname);
	}
	ft_putstr_fd("cannot access '", 2);
	ft_putstr_fd(args[0], 2);
	perror("'");
	exit(EXIT_FAILURE);
}

/*
Execute a built-in commands, or an external program. Returns 0 upon
successful execution, or non-zero upon failure.
*/
static void	ft_builtin_or_execute(t_scmd *scmd)
{
	char		**args;
	const char	*built_in[] = {"echo", "cd", "pwd",
							   "export", "unset", "env", "exit"};
	static int	(*func[])(char **) = {&ft_echo, &ft_cd, &ft_pwd,
									  &ft_export, &ft_unset, &ft_env, &ft_exit};
	const int	n = sizeof(built_in) / sizeof(built_in[0]);
	int			i;

	args = ft_scmd_to_arr(scmd);
	i = -1;
	while (++i < n)
	{
		if (ft_strncmp(args[0], built_in[i], ft_strlen(built_in[i]) + 1) == 0)
			exit(func[i](args));
	}
	ft_exec_external(args);
}

/*
Execute the i-th command in the t_cmd by forking. After the fork, the
child process will execute a program while the parent process will
return the pid of the child process.
*/
pid_t	ft_execute_scmd(t_cmd *cmd, int i)
{
	static int		fd_in = -1;
	int				fd_pipe[2];
	pid_t			pid;

	if (fd_in == -1 && cmd->infile != NULL)
		fd_in = open_infile(cmd);
	if (fd_in == -1 && cmd->infile != NULL)
		return (-1);
	if (i < cmd->count - 1)
		ft_pipe_create(fd_pipe);
	else
	{
		fd_pipe[0] = -1;
		fd_pipe[1] = open_outfile(cmd);
	}
	pid = ft_fork();
	ft_fd_cleanup(pid, &fd_in, fd_pipe);
	if (pid == 0)
		ft_builtin_or_execute(cmd->scmd_lst->content);
	return (pid);
}

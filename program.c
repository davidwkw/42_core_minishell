/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 10:09:22 by weng              #+#    #+#             */
/*   Updated: 2022/01/05 13:52:38 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the pointer to the built-in command given by 'name' */
t_bif	ft_builtin(char *name)
{
	const char	*cmd[] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", "history"};
	const t_bif	func[] = {&ft_echo, &ft_cd, &ft_pwd, &ft_export,
		&ft_unset, &ft_env, &ft_exit, &ft_history};
	const int	n = sizeof(cmd) / sizeof(cmd[0]);
	int			i;

	i = -1;
	while (++i < n)
	{
		if (ft_strncmp(name, cmd[i], ft_strlen(cmd[i]) + 1) == 0)
			return (func[i]);
	}
	return (NULL);
}

/* Execute an external program, or raises error if program is not found. */
void	ft_external(char **args)
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
			execve(pathname, args, g_environ);
		free(pathname);
	}
	if (access(args[0], F_OK) == 0)
		execve(args[0], args, g_environ);
	ft_putstr_fd("cannot access '", 2);
	ft_putstr_fd(args[0], 2);
	perror("'");
	exit(EXIT_FAILURE);
}

/* Run a built_in program or an external program. */
void	ft_run(char **arg, int nofork)
{
	t_bif	func;
	int		retval;

	func = ft_builtin(arg[0]);
	if (func != NULL)
		retval = func(arg);
	else
		ft_external(arg);
	if (nofork == 0)
		exit(retval);
}

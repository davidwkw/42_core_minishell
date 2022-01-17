/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 10:09:22 by weng              #+#    #+#             */
/*   Updated: 2022/01/17 23:29:18 by weng             ###   ########.fr       */
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
		if (ft_strcmp(name, cmd[i]) == 0)
			return (func[i]);
	}
	return (NULL);
}

/*
Checks whether args[0] is a directory or whether it exists. Exit upon error.
*/
static void	ft_external_error(char **args)
{
	struct stat	statbuf;

	if (stat(args[0], &statbuf) == 0 && S_ISDIR(statbuf.st_mode) == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
	else if (access(args[0], F_OK) != 0)
	{
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}

/* Execute an external program, or raises error if program is not found. */
void	ft_external(char **args)
{
	char	**dirs;
	char	*pathname;
	int		i;

	ft_sighandler_default();
	dirs = ft_split(ft_getenv("PATH"), ':');
	i = -1;
	while (dirs[++i] != NULL
		&& ft_strncmp(args[0], "./", 2) != 0
		&& ft_strncmp(args[0], "../", 3) != 0)
	{
		pathname = ft_pathjoin(dirs[i], args[0]);
		if (access(pathname, F_OK) == 0)
			execve(pathname, args, g_environ);
		free(pathname);
	}
	ft_external_error(args);
	execve(args[0], args, g_environ);
	exit(0);
}

/* Run a built_in program or an external program. */
void	ft_run(t_list *argv, int nofork)
{
	t_bif	func;
	int		retval;
	char	**arg;
	char	*str;

	arg = ft_lst_to_arr(argv);
	func = ft_builtin(arg[0]);
	if (func != NULL)
		retval = func(arg);
	else
		ft_external(arg);
	ft_arrclear(arg, free);
	if (nofork == 0)
		exit(retval);
	else
	{
		str = ft_itoa(retval);
		str = ft_strreplace(str, ft_strjoin("?=", str));
		ft_putenv(str);
		free(str);
	}
}

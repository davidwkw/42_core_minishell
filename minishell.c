/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:03 by weng              #+#    #+#             */
/*   Updated: 2021/12/30 15:38:39 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_environ;

/* Initialise environment variable array g_environ and ? variable. */
static void	ft_init_environment(void)
{
	g_environ = ft_memdup((const char **) environ);
	ft_putenv("?=0");
}

/*
Forks the process, and the child executes the command. Parent returns
1 if successful, or 0 if not.
*/
static int	ft_fork_exec(char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		(void) args;
		return (EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return (EXIT_SUCCESS);
	}
}

/*
Execute a built-in commands, or an external program. Returns 0 upon
successful execution, or non-zero upon failure.
*/
static int	ft_builtin_or_execute(char **args)
{
	const char	*built_in[] = {"echo", "cd", "pwd",
							   "export", "unset", "env", "exit"};
	static int	(*func[])(char **) = {&ft_echo, &ft_cd, &ft_pwd,
									  &ft_export, &ft_unset, &ft_env, &ft_exit};
	int			n;
	int			i;

	n = sizeof(built_in) / sizeof(built_in[0]);
	if (*args == NULL)
		return (1);
	i = 0;
	while (i < n)
	{
		if (ft_strncmp(args[0], built_in[i], ft_strlen(built_in[i]) + 1) == 0)
			return (func[i](args));
		i++;
	}
	return (ft_fork_exec(args));
}

/*
Runs an infinite loop, during which, user input is read, split and
executed. The loop exits if return value from execution is not 1.
If user returns a bare newline, loop is skipped without splitting the string.
*/
static void	ft_loop(void)
{
	char	*line;
	char	**args;
	int		status;
	int		i;

	status = EXIT_SUCCESS;
	while (status == EXIT_SUCCESS)
	{
		line = readline("$ ");
		if (line == NULL)
			break ;
		else if (!ft_strlen(line))
			continue ;
		add_history(line);
		args = ft_split(line, ' ');
		status = ft_builtin_or_execute(args);
		free(line);
		i = -1;
		while (args[++i] != NULL)
			free(args[i]);
		free(args);
	}
}

int	main(void)
{
	ft_init_environment();
	ft_loop();
	ft_memdel(g_environ);
	return (EXIT_SUCCESS);
}

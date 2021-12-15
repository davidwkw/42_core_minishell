/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:03 by weng              #+#    #+#             */
/*   Updated: 2021/12/15 14:43:09 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{	
		(void) args;
		return (EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return (1);
	}
}

/* Execute a built-in commands, or an external program. */
static int	ft_builtin_or_execute(char **args)
{
	if (*args == NULL)
		return (1);
	return (ft_fork_exec(args));
}

/*
Runs an infinite loop, during which, user input is read, split and
executed. The loop exits if return value from execution is not 1.
*/
static void	ft_loop(void)
{
	char	*line;
	char	**args;
	int		status;
	int		i;

	status = 1;
	while (status == 1)
	{
		line = readline("$ ");
		if (line == NULL)
			break ;
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
	ft_loop();
	return (EXIT_SUCCESS);
}

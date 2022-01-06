/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:03 by weng              #+#    #+#             */
/*   Updated: 2022/01/06 14:01:06 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

/* Initialise environment variable array g_global.environ_vars and ? variable. */
static void	ft_init_environment(char **env)
{
	g_global.environ_vars = ft_memdup((const char **) env);
	ft_putenv("?=0");
}

/* Read and execute one line from user input. */
static int	ft_read_execute(void)
{
	char	*line;
	t_cmd	*cmd;

	line = readline("$ ");
	if (line == NULL)
		return (0);
	else if (*line == '\0')
		return (1);
	save_history(line);
	cmd = ft_parse(ft_tokenise(line));
	ft_execute_cmd(cmd);
	free(line);
	unlink(HEREDOC_FILE);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_init_environment(envp);
	ft_init_history();
	ft_init_signals();
	while (ft_read_execute())
		;
	ft_memdel(g_global.environ_vars);
	return (EXIT_SUCCESS);
}

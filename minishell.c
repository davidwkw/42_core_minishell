/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:03 by weng              #+#    #+#             */
/*   Updated: 2022/01/11 14:44:57 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_environ;

/* Initialise environment variable array g_environ and ? variable. */
static void	ft_init_environment(char **env)
{
	g_environ = ft_memdup((const char **) env);
	ft_putenv("?=0");
}

/* Read and execute one line from user input. */
static void	ft_read_execute(void)
{
	char	*line;
	t_cmd	*cmd;

	line = readline("$ ");
	if (line == NULL || *line == '\0')
		return ;
	save_history(line);
	cmd = ft_parse(ft_tokenise(line));
	ft_execute_cmd(cmd);
	free(line);
	unlink(HEREDOC_FILE);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	ft_init_environment(env);
	ft_init_history();
	while (1)
		ft_read_execute();
	ft_memdel(g_environ);
	return (EXIT_SUCCESS);
}

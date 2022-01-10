/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:03 by weng              #+#    #+#             */
/*   Updated: 2022/01/10 10:54:10 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Read and execute one line from user input. */
static void	ft_read_execute(void)
{
	char	*line;
	t_list	*token;
	t_list	*token_cpy;
	t_cmd	*cmd;

	line = readline("$ ");
	if (line == NULL || *line == '\0')
		return ;
	save_history(line);
	token = ft_tokenise(line);
	token_cpy = token;
	cmd = ft_parse(&token);
	ft_execute_cmd(cmd);
	ft_lstclear(&token_cpy, free);
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

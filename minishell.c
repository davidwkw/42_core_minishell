/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:03 by weng              #+#    #+#             */
/*   Updated: 2022/01/04 09:55:09 by weng             ###   ########.fr       */
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

static void	lst_wait(void *content)
{
	waitpid(*((pid_t *) content), NULL, 0);
}

/*
Runs an infinite loop, during which, user input is read, split and
executed. The loop exits if return value from execution is not 1.
*/
static void	ft_loop(void)
{
	char	*line;
	t_list	*lst;
	t_cmd	*cmd;
	pid_t	pid;
	int		i;

	lst = NULL;
	while (1)
	{
		line = readline("$ ");
		cmd = ft_parse(ft_tokenise(line));
		i = -1;
		while (++i < cmd->count)
		{
			pid = ft_execute_scmd(cmd, i);
			ft_lstadd_back(&lst, ft_lstnew(&pid));
		}
		ft_lstiter(lst, lst_wait);
		ft_lstclear(&lst, NULL);
		ft_cmd_del(cmd);
		free(line);
		unlink(".heredoc");
	}
}

int	main(void)
{
	ft_init_environment();
	ft_loop();
	ft_memdel(g_environ);
	return (EXIT_SUCCESS);
}

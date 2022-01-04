/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:03 by weng              #+#    #+#             */
/*   Updated: 2022/01/04 14:00:58 by weng             ###   ########.fr       */
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

/* Read and execute one line from user input. */
static void	ft_read_execute(void)
{
	char	*line;
	t_list	*lst;
	t_cmd	*cmd;
	pid_t	pid;
	int		i;

	lst = NULL;
	ft_save_restore_fd();
	line = readline("$ ");
	cmd = ft_parse(ft_tokenise(line));
	i = -1;
	while (++i < cmd->count)
	{
		pid = ft_execute_scmd(cmd, i);
		if (pid > 0)
			ft_lstadd_back(&lst, ft_lstnew(&pid));
	}
	ft_lstiter(lst, lst_wait);
	ft_lstclear(&lst, NULL);
	ft_cmd_del(cmd);
	free(line);
	unlink(".heredoc");
	ft_save_restore_fd();
}

int	main(void)
{
	ft_init_environment();
	while (1)
		ft_read_execute();
	ft_memdel(g_environ);
	return (EXIT_SUCCESS);
}

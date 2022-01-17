/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:03 by weng              #+#    #+#             */
/*   Updated: 2022/01/17 10:30:47 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return a colorised prompt string. */
static char	*ft_get_cwd_prompt(void)
{
	char	*cwd_prompt;
	char	*dir;
	char	*temp;

	dir = getcwd(NULL, 0);
	temp = ft_strjoin(BOLD GREEN, dir);
	free(dir);
	dir = ft_strjoin(temp, NORMAL);
	free(temp);
	cwd_prompt = ft_strjoin(dir, "$ ");
	free(dir);
	return (cwd_prompt);
}

/*
Read and execute one line from user input. Return 1 if line is not NULL,
0 otherwise.
*/
static int	ft_read_execute(void)
{
	char	*prompt;
	char	*line;
	t_list	*token;
	t_ptree	*ptree;

	ft_sighandler_shell();
	prompt = ft_get_cwd_prompt();
	line = readline(prompt);
	if (line == NULL)
		return (0);
	if (*line != '\0')
	{
		ft_history_save(line);
		token = ft_tokenise(line);
		ptree = ft_treeify(token);
		ft_execute_ptree(ptree);
		ft_ptree_clear(ptree);
	}
	free(line);
	free(prompt);
	unlink(HEREDOC_FILE);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int	exit_value;

	(void)argc;
	(void)argv;
	ft_init_environment(envp);
	ft_init_history();
	while (ft_read_execute())
		;
	printf("exit\n");
	exit_value = ft_atoi(ft_getenv("?"));
	ft_arrclear(g_environ, free);
	return (exit_value);
}

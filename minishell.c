/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:03 by weng              #+#    #+#             */
/*   Updated: 2022/01/06 10:21:42 by weng             ###   ########.fr       */
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

/* Put the non-zero pid into a linked list */
static void	ft_record_pid(t_list **lst, pid_t pid)
{
	int	*ptr;

	if (pid == 0)
		return ;
	ptr = malloc(sizeof(int));
	if (ptr != NULL)
		*ptr = pid;
	ft_lstadd_back(lst, ft_lstnew(ptr));
}

/* Wait for the end each child process and put the exit value in environment */
static void	ft_set_exit_value(t_cmd *cmd, t_list *lst)
{
	pid_t	*pid;
	int		wstatus;
	int		value;
	char	*val_str;
	char	*str;

	if (cmd->count == 0 && cmd->infile == NULL && cmd->outfile == NULL)
		return ;
	value = 0;
	while (lst != NULL)
	{
		pid = lst->content;
		waitpid(*pid, &wstatus, WUNTRACED);
		value |= WEXITSTATUS(wstatus);
		lst = lst->next;
	}
	val_str = ft_itoa(value);
	str = ft_strjoin("?=", val_str);
	ft_putenv(str);
	free(val_str);
	free(str);
}

/* Read and execute one line from user input. */
static void	ft_read_execute(void)
{
	char	*line;
	t_list	*lst;
	t_cmd	*cmd;
	int		i;

	line = readline("$ ");
	if (line == NULL || *line == '\0')
		return ;
	lst = NULL;
	ft_save_restore_fd();
	save_history(line);
	cmd = ft_parse(ft_tokenise(line));
	i = -1;
	while (++i < cmd->count)
		ft_record_pid(&lst, ft_execute_scmd(cmd, i));
	ft_set_exit_value(cmd, lst);
	ft_lstclear(&lst, free);
	ft_cmd_del(cmd);
	free(line);
	unlink(HEREDOC_FILE);
	ft_save_restore_fd();
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

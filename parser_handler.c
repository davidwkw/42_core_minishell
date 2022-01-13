/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:21:45 by weng              #+#    #+#             */
/*   Updated: 2022/01/13 15:52:37 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Records to the input redirection information. Returns -1 upon error,
0 otherwise.
*/
static int	ft_hdlr_input(t_cmd *cmd, t_list **lst)
{
	t_list	*node;
	char	*content;
	int		fd;

	node = (*lst)->next;
	content = (*lst)->content;
	if (node == NULL || ft_istoken(node->content, NULL, 0) == 1)
		return (ft_parse_error(node));
	*lst = node;
	if (ft_strncmp(content, "<<", 2) == 0)
	{
		ft_strreplace(&(cmd->infile), ft_strdup(HEREDOC_FILE));
		return (ft_write_heredoc(node->content));
	}
	else if (ft_strncmp(content, "<", 1) == 0)
	{
		ft_strreplace(&(cmd->infile), ft_strdup(node->content));
		fd = ft_open(node->content, O_RDONLY, 0);
		if (fd == -1)
			return (-1);
		return (ft_close(fd));
	}
	return (-1);
}

/*
Records to the output redirection information. Returns -1 upon error,
0 otherwise.
*/
static int	ft_hdlr_output(t_cmd *cmd, t_list **lst)
{
	t_list	*node;
	char	*content;
	int		fd;

	node = (*lst)->next;
	content = (*lst)->content;
	if (node == NULL || ft_istoken(node->content, NULL, 0) == 1)
		return (ft_parse_error(node));
	*lst = node;
	ft_strreplace(&(cmd->outfile), ft_strdup(node->content));
	if (ft_strncmp(content, ">>", 2) == 0)
		cmd->outfile_flag = O_APPEND;
	else
		cmd->outfile_flag = O_TRUNC;
	fd = ft_open(node->content, O_CREAT | cmd->outfile_flag, S_IWUSR);
	if (fd == -1)
		return (-1);
	return (ft_close(fd));
}

/*
Instantiate a simple command in 'cmd'. If the cmd is empty, or if the
current simple command is empty, error is raised.
*/
static int	ft_hdlr_pipe(t_cmd *cmd, t_list **lst)
{
	t_scmd	*scmd;

	if (cmd->count == 0 && cmd->infile == NULL && cmd->outfile == NULL)
		return (ft_parse_error(*lst));
	scmd = ft_cmd_get_scmd(cmd, cmd->count - 1);
	if (scmd->count == 0)
		return (ft_parse_error(*lst));
	ft_cmd_add_scmd(cmd);
	return (0);
}

/* Identify and run the correct token handler function */
int	ft_hdlr_token(t_cmd *cmd, t_list **lst)
{
	const char	*substr[] = {"<<", ">>", "<", ">", "|"};
	static int	(*hdlr[])(t_cmd *, t_list **) = {
		&ft_hdlr_input, &ft_hdlr_output, &ft_hdlr_input,
		&ft_hdlr_output, &ft_hdlr_pipe};
	int			i;
	char		*token;

	ft_istoken((*lst)->content, &token, 0);
	i = 0;
	while (i < (long)(sizeof(substr) / sizeof(substr[0])))
	{
		if (ft_strncmp(token, substr[i], ft_strlen(substr[i]) + 1) == 0)
		{
			free(token);
			return ((hdlr[i])(cmd, lst));
		}
		i++;
	}
	free(token);
	return (ft_parse_error(*lst));
}

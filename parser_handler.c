/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:21:45 by weng              #+#    #+#             */
/*   Updated: 2021/12/30 13:22:07 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Records to the indirection information to the correct fields. Returns
-1 if error occurs, else 0.
*/
static int	ft_hdlr_redirect(t_cmd *cmd, t_list **lst)
{
	t_list	*node;
	char	*content;

	node = *lst;
	content = node->content;
	if (node->next == NULL)
		return (ft_parse_error(cmd, lst));
	else if (ft_istoken(node->next->content, NULL) == 1)
		return (ft_parse_error(cmd, &(node->next)));
	node = node->next;
	if (*(content) == '<')
	{
		ft_strreplace(&(cmd->infile), ft_strdup(node->content));
		cmd->heredoc = content[1] == '<';
	}
	else
	{
		ft_strreplace(&(cmd->outfile), ft_strdup(node->content));
		cmd->append = content[1] == '>';
	}
	*lst = node;
	return (0);
}

/*
Instantiate a simple command in 'cmd'. If the current simple command is
empty, error is raised.
*/
static int	ft_hdlr_pipe(t_cmd *cmd, t_list **lst)
{
	t_scmd	*scmd;

	scmd = cmd->scmd_lst->content;
	if (scmd->count == 0)
		return (ft_parse_error(cmd, lst));
	ft_cmd_add_scmd(cmd);
	return (0);
}

/*
Terminate a command. If the newline token is not the last in the list,
error is raised.
*/
static int	ft_hdlr_newline(t_cmd *cmd, t_list **lst)
{
	if ((*lst)->next != NULL)
		return (ft_parse_error(cmd, lst));
	return (0);
}

/* Identify and run the correct token handler function */
int	ft_hdlr_token(t_cmd *cmd, t_list **lst)
{
	const char	*substr[] = {"<<", ">>", "<", ">", "|", "&", "\n"};
	static int	(*hdlr[])(t_cmd *, t_list **) = {
		&ft_hdlr_redirect, &ft_hdlr_redirect, &ft_hdlr_redirect,
		&ft_hdlr_redirect, &ft_hdlr_pipe, &ft_parse_error, &ft_hdlr_newline};
	int			i;
	char		*token;

	ft_istoken((*lst)->content, &token);
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
	return (ft_parse_error(cmd, lst));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:21:45 by weng              #+#    #+#             */
/*   Updated: 2022/01/18 09:44:15 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Carry out variable expansion, asterisk expansion and quote removal, and
detect ambiguous redirect.
*/
static char	*ft_redirect_file(char *content)
{
	t_list	*files;
	char	*str;
	char	*retval;

	str = ft_expand_var(content);
	files = ft_expand_star(NULL, str);
	if (ft_lstsize(files) > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(content, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		retval = NULL;
	}
	else
	{
		retval = ft_strtrim(files->content, " ");
		retval = ft_strreplace(retval, ft_remove_quote(retval));
	}
	ft_lstclear(&files, free);
	free(str);
	return (retval);
}

/*
Records to the input redirection information. Returns -1 upon error,
0 otherwise.
*/
static int	ft_hdlr_redirect(t_cmd *cmd, t_list **lst)
{
	t_list	*node;
	char	*filename;
	char	*content;
	t_scmd	*scmd;
	t_inout	*inout;

	node = (*lst)->next;
	content = (*lst)->content;
	if (node == NULL || ft_istoken(node->content, NULL, 0) == 1)
		return (ft_parse_error(node));
	*lst = node;
	filename = ft_redirect_file(node->content);
	if (filename == NULL)
		return (-1);
	scmd = ft_lstlast(cmd->scmd_lst)->content;
	inout = ft_inout_new(ft_strlen(content), filename);
	if (inout == NULL)
		return (-1);
	if (*content == '<')
		ft_lstadd_back(&scmd->infile, ft_lstnew(inout));
	else
		ft_lstadd_back(&scmd->outfile, ft_lstnew(inout));
	return (0);
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
	scmd = ft_lstlast(cmd->scmd_lst)->content;
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
		&ft_hdlr_redirect, &ft_hdlr_redirect, &ft_hdlr_redirect,
		&ft_hdlr_redirect, &ft_hdlr_pipe};
	int			i;
	char		*token;

	ft_istoken((*lst)->content, &token, 0);
	i = 0;
	while (i < (long)(sizeof(substr) / sizeof(substr[0])))
	{
		if (ft_strcmp(token, substr[i]) == 0)
		{
			free(token);
			return ((hdlr[i])(cmd, lst));
		}
		i++;
	}
	free(token);
	return (ft_parse_error(*lst));
}

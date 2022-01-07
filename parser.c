/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:06:28 by weng              #+#    #+#             */
/*   Updated: 2022/01/07 17:44:49 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print an error message upon unexpected token. Returns -1. */
int	ft_parse_error(t_cmd *cmd, t_list **lst)
{
	char	*token;

	(void) cmd;
	if (*lst == NULL)
		token = ft_strdup("newline");
	else
		ft_istoken((*lst)->content, &token);
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	free(token);
	return (-1);
}

/* Parse the tokens returned from ft_tokenise into a t_cmd struct */
t_cmd	*ft_parse(t_list *lst)
{
	t_cmd		*cmd;
	t_list		*node;

	cmd = ft_cmd_new();
	if (lst == NULL)
		return (cmd);
	node = lst;
	while (node != NULL)
	{
		if (ft_istoken(node->content, NULL) == 1)
			ft_hdlr_token(cmd, &node);
		else
			ft_cmd_add_arg(cmd, node);
		node = node->next;
	}
	ft_lstclear(&lst, free);
	return (cmd);
}

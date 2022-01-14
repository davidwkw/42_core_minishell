/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:06:28 by weng              #+#    #+#             */
/*   Updated: 2022/01/14 15:06:28 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print an error message upon unexpected token. Returns -1. */
int	ft_parse_error(t_list *lst)
{
	char	*token;

	if (lst == NULL)
		token = "newline";
	else
		token = lst->content;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	return (-1);
}

/* Return 1 if token is one of "||", "&&", ")" or NULL, else 0 */
static int	ft_is_end_of_command(t_list *lst)
{
	return (lst == NULL
		|| ft_strcmp(lst->content, "&&") == 0
		|| ft_strcmp(lst->content, "||") == 0
		|| ft_strcmp(lst->content, ")") == 0);
}

/* Parse the tokens returned from ft_tokenise into a t_cmd struct */
t_cmd	*ft_parse(t_list **lst)
{
	t_cmd	*cmd;
	int		status;

	cmd = ft_cmd_new();
	status = 0;
	while (ft_is_end_of_command(*lst) == 0 && status == 0)
	{
		if (ft_istoken((*lst)->content, NULL, 0) == 1)
			status = ft_hdlr_token(cmd, lst);
		else
			ft_cmd_add_arg(cmd, *lst);
		*lst = (*lst)->next;
	}
	if (status != -1
		&& cmd->count > 0 && ft_cmd_get_scmd(cmd, cmd->count - 1)->count == 0)
		status = ft_parse_error(*lst);
	if (status == -1)
	{
		ft_cmd_del(cmd);
		cmd = NULL;
	}
	return (cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:24:17 by weng              #+#    #+#             */
/*   Updated: 2022/01/19 10:24:02 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns a new command structure. */
t_cmd	*ft_cmd_new(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	return (cmd);
}

/* Deletes a command structure, as well as the linked list 'scmd'. */
void	ft_cmd_del(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	ft_lstclear(&cmd->scmd, (void (*)(void *)) ft_scmd_del);
	free(cmd);
}

/* Add a new simple command to the end of the scmd linked list. */
void	ft_cmd_add_scmd(t_cmd *cmd)
{
	t_scmd	*scmd;

	scmd = ft_scmd_new();
	scmd->index = cmd->count;
	ft_lstadd_back(&cmd->scmd, ft_lstnew(scmd));
	cmd->count++;
}

/* Add an argument to the last node in linked list. */
void	ft_cmd_add_arg(t_cmd *cmd, t_list *node)
{
	t_list	*last;

	last = ft_lstlast(cmd->scmd);
	if (last == NULL)
	{
		ft_cmd_add_scmd(cmd);
		last = cmd->scmd;
	}
	ft_scmd_add_arg(last->content, node);
}

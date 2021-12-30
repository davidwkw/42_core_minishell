/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:24:17 by weng              #+#    #+#             */
/*   Updated: 2021/12/30 10:51:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns a new command structure. */
t_cmd	*ft_cmd_new(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	ft_cmd_add_scmd(cmd);
	return (cmd);
}

/* Deletes a command structure, as well as the linked list 'scmd'. */
void	ft_cmd_del(t_cmd *cmd)
{
	ft_lstclear(&cmd->scmd_lst, ft_scmd_del);
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd);
}

/* Add a new simple command to the end of the scmd linked list. */
void	ft_cmd_add_scmd(t_cmd *cmd)
{
	ft_lstadd_back(&cmd->scmd_lst, ft_lstnew(ft_scmd_new()));
	cmd->count++;
}

/* Add an argument to the last node in linked list. */
void	ft_cmd_add_arg(t_cmd *cmd, t_list *node)
{
	t_list	*last;

	last = ft_lstlast(cmd->scmd_lst);
	ft_scmd_add_arg(last->content, node);
}

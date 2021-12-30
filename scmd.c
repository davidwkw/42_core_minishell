/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:56:05 by weng              #+#    #+#             */
/*   Updated: 2021/12/29 16:00:24 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a new simple command */
t_scmd	*ft_scmd_new(void)
{
	t_scmd	*scmd;

	scmd = ft_calloc(sizeof(t_scmd), 1);
	return (scmd);
}

/* Delete a simple command. */
void	ft_scmd_del(void *scmd)
{
	t_scmd	*scmd_;

	scmd_ = scmd;
	ft_lstclear(&(scmd_->argv), free);
	free(scmd);
}

/* 
Add an argument to a simple command.

The content of 'node' is duplicated, and a new node is added to the back
of scmd->argv.
*/
void	ft_scmd_add_arg(t_scmd *scmd, t_list *node)
{
	char	*content;

	content = ft_strdup(node->content);
	ft_lstadd_back(&(scmd->argv), ft_lstnew(content));
	scmd->count++;
}

/* Convert all arguments in a simple command to an array of strings. */
char	**ft_scmd_to_arr(t_scmd *scmd)
{
	return (ft_lst_to_arr(scmd->argv));
}
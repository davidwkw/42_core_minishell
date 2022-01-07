/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:48:47 by weng              #+#    #+#             */
/*   Updated: 2022/01/07 11:16:37 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns a new ptree node. */
t_ptree	*ft_ptree_new(void *content, t_ptree_type type)
{
	t_ptree	*node;

	node = malloc(sizeof(t_ptree));
	if (node != NULL)
	{
		node->content = content;
		node->type = type;
		node->left = NULL;
		node->right = NULL;
	}
	return (node);
}

/* Deletes a ptree node */
void	ft_ptree_delone(t_ptree *node)
{
	if (node->type == TOKEN)
		free(node->content);
	else if (node->type == CMD)
		ft_cmd_del(node->content);
	free(node);
}

/* Deletes a whole ptree using postfix traversal. */
void	ft_ptree_clear(t_ptree *node)
{
	if (node->left != NULL)
		ft_ptree_clear(node->left);
	if (node->right != NULL)
		ft_ptree_clear(node->right);
	ft_ptree_delone(node);
}

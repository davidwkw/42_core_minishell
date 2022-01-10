/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:48:47 by weng              #+#    #+#             */
/*   Updated: 2022/01/10 16:49:23 by weng             ###   ########.fr       */
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
	if (node == NULL)
		return ;
	ft_ptree_clear(node->left);
	ft_ptree_clear(node->right);
	ft_ptree_delone(node);
}

/* Returns the height of a ptree */
int	ft_ptree_height(t_ptree	*node)
{
	int	height_l;
	int	height_r;

	if (node == NULL)
		return (0);
	height_l = ft_ptree_height(node->left);
	height_r = ft_ptree_height(node->right);
	if (height_l > height_r)
		return (height_l + 1);
	else
		return (height_r + 1);
}

/* Apply function 'func' to each node using prefix traversal */
void	ft_ptree_apply_prefix(t_ptree *node, void (*func)(t_ptree *))
{
	if (node == NULL || func == NULL)
		return ;
	func(node);
	ft_ptree_apply_prefix(node->left, func);
	ft_ptree_apply_prefix(node->right, func);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:47:51 by weng              #+#    #+#             */
/*   Updated: 2022/01/14 15:06:06 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ptree	*ft_treeify_aux(t_ptree *ptree, t_list **lst);

/* Adds a && or || node as parent of 'ptree' node. Returns the new node. */
static t_ptree	*ft_tree_hdlr_token(t_ptree *ptree, t_list **lst)
{
	t_ptree	*parent;

	if (ptree == NULL)
	{
		ft_parse_error(*lst);
		return (NULL);
	}
	parent = ft_ptree_new(ft_strdup((*lst)->content), TOKEN);
	parent->left = ptree;
	*lst = (*lst)->next;
	return (parent);
}

/*
Generates a cmd node. If 'ptree' is NULL, the cmd node is returned, else
it is attached as the right child of 'ptree'.
*/
static t_ptree	*ft_tree_hdlr_cmd(t_ptree *ptree, t_list **lst)
{
	t_cmd	*cmd;

	if (ptree != NULL && (ptree->type != TOKEN || ptree->right != NULL))
	{
		ft_parse_error(*lst);
		ft_ptree_clear(ptree);
		return (NULL);
	}
	cmd = ft_parse(lst);
	if (ptree == NULL)
		ptree = ft_ptree_new(cmd, CMD);
	else
		ptree->right = ft_ptree_new(cmd, CMD);
	return (ptree);
}

/* Generates a parse tree.

This function is called at the beginning of treeify, or at a "(" token;
and returns at *lst == NULL, or at a ")" token.
*/
static t_ptree	*ft_tree_hdlr_tree(t_ptree *ptree, t_list **lst)
{
	t_ptree	*branch;

	if (ptree != NULL && (ptree->type != TOKEN || ptree->right != NULL))
	{
		ft_parse_error(*lst);
		ft_ptree_clear(ptree);
		return (NULL);
	}
	*lst = (*lst)->next;
	branch = ft_treeify_aux(NULL, lst);
	if (branch->type == TOKEN && branch->right == NULL)
	{
		ft_parse_error(*lst);
		ft_ptree_clear(ptree);
		ft_ptree_clear(branch);
		return (NULL);
	}
	if (ptree == NULL)
		ptree = branch;
	else
		ptree->right = branch;
	*lst = (*lst)->next;
	return (ptree);
}

/*
Auxiliary treeify function to be call by treeify or related functions.
Creates a ptree node every loop, and returns at ")" token or end of list.
*/
static t_ptree	*ft_treeify_aux(t_ptree *ptree, t_list **lst)
{
	char	*content;

	while (*lst != NULL && ft_strcmp((*lst)->content, ")") != 0)
	{
		content = (*lst)->content;
		if (ft_strcmp(content, "(") == 0)
			ptree = ft_tree_hdlr_tree(ptree, lst);
		else if (ft_strcmp(content, "&&") == 0 || ft_strcmp(content, "||") == 0)
			ptree = ft_tree_hdlr_token(ptree, lst);
		else
			ptree = ft_tree_hdlr_cmd(ptree, lst);
		if (ptree == NULL)
			break ;
	}
	return (ptree);
}

/* Parse a linked list of tokens into parse tree. */
t_ptree	*ft_treeify(t_list *lst)
{
	t_ptree	*ptree;
	t_list	*node;

	if (lst == NULL)
		return (NULL);
	ptree = NULL;
	node = lst;
	ptree = ft_treeify_aux(NULL, &node);
	ft_lstclear(&lst, free);
	return (ptree);
}

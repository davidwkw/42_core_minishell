/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 23:14:33 by weng              #+#    #+#             */
/*   Updated: 2022/01/13 12:56:29 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free and replace the content of lst with a new content. */
void	ft_lst_replace_content(t_list *lst, void *content)
{
	free(lst->content);
	lst->content = content;
}

/* Insert a new node as 'next' of 'lst'. */
void	ft_lstinsert(t_list *lst, t_list *new)
{
	new->next = lst->next;
	lst->next = new;
}

/* Remove nodes where the content is an empty string */
t_list	*ft_lstdel_if_equal(
	t_list **lst, int (*cmp)(void *, void *), void *arg, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	node = *lst;
	while (node != NULL && cmp(node->content, arg) == 0)
	{
		node = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = node;
	}
	while (node != NULL && node->next != NULL)
	{
		next = node->next;
		if (cmp(next->content, arg) == 0)
		{
			node->next = next->next;
			ft_lstdelone(next, del);
		}
		else
			node = node->next;
	}
	return (*lst);
}

/*
Convert a linked list to an array of strings. The contents from the
linked list are duplicated into the array.
*/
char	**ft_lst_to_arr(t_list *lst)
{
	int		size;
	int		i;
	char	**arr;

	size = ft_lstsize(lst);
	arr = ft_calloc(sizeof(char *), size + 1);
	i = -1;
	while (++i < size)
	{
		arr[i] = ft_strdup(lst->content);
		lst = lst->next;
	}
	return (arr);
}

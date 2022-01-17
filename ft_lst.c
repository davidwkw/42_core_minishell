/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 23:14:33 by weng              #+#    #+#             */
/*   Updated: 2022/01/17 15:45:58 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Remove nodes if cmp(lst->content, arg) evaluates to 0. The content of
the removed nodes are deleted using the function 'del'.
*/
t_list	*ft_lstdelif(
	t_list *lst, int (*cmp)(void *, void *), void *arg, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	node = lst;
	while (node != NULL && cmp(node->content, arg) == 0)
	{
		node = lst->next;
		ft_lstdelone(lst, del);
		lst = node;
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
	return (lst);
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

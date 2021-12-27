/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 23:14:33 by weng              #+#    #+#             */
/*   Updated: 2021/12/27 23:19:55 by weng             ###   ########.fr       */
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
t_list	*ft_lstdelempty(t_list **lst)
{
	t_list	*node;
	t_list	*next;

	node = *lst;
	while (node != NULL && *((char *) node->content) == '\0')
	{
		node = (*lst)->next;
		ft_lstdelone(*lst, free);
		*lst = node;
	}
	while (node != NULL && node->next != NULL)
	{
		next = node->next;
		if (*((char *) next->content) == '\0')
		{
			node->next = next->next;
			ft_lstdelone(next, free);
		}
		else
			node = node->next;
	}
	return (*lst);
}

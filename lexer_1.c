/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 01:06:46 by weng              #+#    #+#             */
/*   Updated: 2021/12/26 01:20:10 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Split the content of lst at '|' characters. If the next character is
also a '|', add the '<||>' token to lst, else add the '<|>' token.

Note: the character '<' and '>' are used to enclose special token.
*/
t_list	*ft_hdlr_pipe(t_list *lst)
{
	t_list	*start;
	char	*content;
	char	*str;
	char	*target;

	start = lst;
	while (lst != NULL)
	{
		content = lst->content;
		target = ft_strchr_unquoted(content, '|');
		if (target != NULL && *content != '<')
		{
			str = ft_substr(content, 0, target - content);
			if (target[1] == '|')
				ft_lstinsert(lst, ft_lstnew(ft_strdup("<||>")));
			else
				ft_lstinsert(lst, ft_lstnew(ft_strdup("<|>")));
			ft_lstinsert(lst->next,
				ft_lstnew(ft_strdup(target + 1 + (target[1] == '|'))));
			ft_lst_replace_content(lst, str);
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (ft_lstdelempty(&start));
}

/*
Split the content of lst at '&' characters. If the next character is
also a '&', add the '<&&>' token to lst, else add the '<&>' token.

Note: the character '<' and '>' are used to enclose special token.
*/
t_list	*ft_hdlr_ampersand(t_list *lst)
{
	t_list	*start;
	char	*content;
	char	*str;
	char	*target;

	start = lst;
	while (lst != NULL)
	{
		content = lst->content;
		target = ft_strchr_unquoted(content, '&');
		if (target != NULL && *content != '<')
		{
			str = ft_substr(content, 0, target - content);
			if (target[1] == '&')
				ft_lstinsert(lst, ft_lstnew(ft_strdup("<&&>")));
			else
				ft_lstinsert(lst, ft_lstnew(ft_strdup("<&>")));
			ft_lstinsert(lst->next,
				ft_lstnew(ft_strdup(target + 1 + (target[1] == '&'))));
			ft_lst_replace_content(lst, str);
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (ft_lstdelempty(&start));
}

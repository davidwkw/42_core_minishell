/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:32:45 by weng              #+#    #+#             */
/*   Updated: 2021/12/26 01:08:09 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns a pointer to the first occurrenc of the character c in the
string s that is not enclosed by matching quote (i.e. ''' or '"'), or
NULL if the character is not found.

The terminating null byte is considered part of the string, so that if
c is specified as '\0', a pointer to the terminator is returned.
*/
char	*ft_strchr_unquoted(const char *str, int c)
{
	char	chr;
	char	quote;

	chr = c;
	quote = '\0';
	while (1)
	{
		if (quote == '\0' && *str == chr)
			return ((char *) str);
		else if (quote == '\0' && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (*str == quote && *str != '\0')
			quote = '\0';
		if (*str == '\0')
			return (NULL);
		str++;
	}
}

/* Tokenize the input and return a linked list. */
t_list	*ft_tokenise(char *input)
{
	t_list	*lst;

	lst = ft_lstnew(ft_strdup(input));
	lst = ft_hdlr_space(lst);
	lst = ft_hdlr_less(lst);
	lst = ft_hdlr_greater(lst);
	lst = ft_hdlr_pipe(lst);
	return (lst);
}

/*
Split the content of lst at space characters. Preceeding spaces are
ignored, and consecutive space are considered as only one space.
*/
t_list	*ft_hdlr_space(t_list *lst)
{
	t_list	*start;
	char	*str;
	char	*target;

	start = lst;
	while (lst != NULL)
	{
		str = lst->content;
		while (*str == ' ')
			str++;
		str = ft_strdup(str);
		ft_lst_replace_content(lst, str);
		target = ft_strchr_unquoted(lst->content, ' ');
		if (target != NULL)
		{
			str = ft_substr(lst->content, 0, target - (char *) lst->content);
			ft_lstinsert(lst, ft_lstnew(ft_strdup(target + 1)));
			ft_lst_replace_content(lst, str);
		}
		lst = lst->next;
	}
	return (ft_lstdelempty(&start));
}

/*
Split the content of lst at '<' characters. If the next character is
also a '<', add the '<<<>' token to lst, else add the '<<>' token.

Note: the character '<' and '>' are used to enclose special token.
*/
t_list	*ft_hdlr_less(t_list *lst)
{
	t_list	*start;
	char	*content;
	char	*str;
	char	*target;

	start = lst;
	while (lst != NULL)
	{
		content = lst->content;
		target = ft_strchr_unquoted(content, '<');
		if (target != NULL)
		{
			str = ft_substr(content, 0, target - content);
			if (target[1] == '<')
				ft_lstinsert(lst, ft_lstnew(ft_strdup("<<<>")));
			else
				ft_lstinsert(lst, ft_lstnew(ft_strdup("<<>")));
			ft_lstinsert(lst->next,
				ft_lstnew(ft_strdup(target + 1 + (target[1] == '<'))));
			ft_lst_replace_content(lst, str);
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (ft_lstdelempty(&start));
}

/*
Split the content of lst at '>' characters. If the next character is
also a '>', add the '<>>>' token to lst, else add the '<>>' token.

Note: the character '<' and '>' are used to enclose special token.
*/
t_list	*ft_hdlr_greater(t_list *lst)
{
	t_list	*start;
	char	*content;
	char	*str;
	char	*target;

	start = lst;
	while (lst != NULL)
	{
		content = lst->content;
		target = ft_strchr_unquoted(content, '>');
		if (target != NULL && *content != '<')
		{
			str = ft_substr(content, 0, target - content);
			if (target[1] == '>')
				ft_lstinsert(lst, ft_lstnew(ft_strdup("<>>>")));
			else
				ft_lstinsert(lst, ft_lstnew(ft_strdup("<>>")));
			ft_lstinsert(lst->next,
				ft_lstnew(ft_strdup(target + 1 + (target[1] == '>'))));
			ft_lst_replace_content(lst, str);
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (ft_lstdelempty(&start));
}

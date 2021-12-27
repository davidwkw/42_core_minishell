/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:03:38 by weng              #+#    #+#             */
/*   Updated: 2021/12/27 22:55:33 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return string if it is properly closed, or and empty string if it is not. */
char	*ft_is_properly_quoted(char *str)
{
	char	quote;
	char	*s;

	quote = '\0';
	s = str;
	while (*s != '\0')
	{
		if (quote == '\0' && (*s == '\'' || *s == '\"'))
			quote = *s;
		else if (*s == quote && *s != '\0')
			quote = '\0';
		s++;
	}
	if (quote == '\0')
		return (str);
	else
	{
		free(str);
		ft_putendl_fd("minishell: unclosed quote detected.", 2);
		return (ft_strdup(""));
	}
}

/*
Returns the pointer to the closest quotation mark that is not enclosed
by other quotation marks, or NULL if no quotation mark is found.
*/
static char	*ft_find_quote(const char *str)
{
	static char	quote = '\0';

	while (*str != '\0')
	{
		if (quote == '\0' && (*str == '\'' || *str == '\"'))
		{
			quote = *str;
			return ((char *) str);
		}
		else if (*str == quote && *str != '\0')
		{
			quote = '\0';
			return ((char *) str);
		}
		str++;
	}
	return (NULL);
}

/* Separate a string into a linked list at quotation marks. */
static t_list	*ft_remove_quote_listify(char *str)
{
	t_list	*node;
	t_list	*lst;
	char	*end;

	lst = ft_lstnew(ft_strdup(str));
	node = lst;
	while (node != NULL)
	{
		end = ft_find_quote(node->content);
		if (end != NULL)
		{
			ft_lstinsert(node, ft_lstnew(ft_strdup(end + 1)));
			ft_lst_replace_content(node,
				ft_substr(node->content, 0, end - (char *) node->content));
		}
		node = node->next;
	}
	return (lst);
}

/* Remove quotation mark from a string. */
char	*ft_remove_quote(char *str)
{
	t_list	*lst;
	t_list	*node;
	char	*retval;

	lst = ft_remove_quote_listify(str);
	node = lst;
	retval = NULL;
	while (node != NULL)
	{
		retval = ft_strappend(retval, node->content);
		node = node->next;
	}
	ft_lstclear(&lst, free);
	return (retval);
}

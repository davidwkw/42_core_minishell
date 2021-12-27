/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:32:45 by weng              #+#    #+#             */
/*   Updated: 2021/12/27 16:18:37 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Return 1 if substring is one of the special tokens, else return 0.

In the event 'token' is not NULL, *token will be set to the copy of the
identified token if it is found, else it will be set to NULL.
*/
int	ft_istoken(const char *str, char **token)
{
	const char	*substr[] = {"<<", ">>", "||", "&&", " ", "<", ">", "|", "&",
							 "(", ")", "\n"};
	const int	n = sizeof(substr) / sizeof(substr[0]);
	int			i;
	int			len;

	i = -1;
	while (++i < n)
	{
		len = ft_strlen(substr[i]);
		if (ft_strncmp(str, substr[i], len) == 0)
		{
			if (token != NULL)
				*token = ft_substr(str, 0, len);
			return (1);
		}
	}
	if (token != NULL)
		*token = NULL;
	return (0);
}

/*
Return the pointer to the first special token along a string, or NULL
if no special token is found.Special token cannot occur at the part of a
string which is enclosed within quote (') or double quote (");
*/
static char	*ft_next_token(const char *str)
{
	char	quote;

	quote = '\0';
	while (1)
	{
		if (quote == '\0' && ft_istoken(str, NULL) == 1)
			return ((char *) str);
		if (quote == '\0' && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (*str == quote && *str != '\0')
			quote = '\0';
		if (*str == '\0')
			return (NULL);
		str++;
	}
}

/*
Tokenize the input and return a linked list. If any of the content
of a node is "" or " ", the node will the removed from the list.
*/
t_list	*ft_tokenise(char *input)
{
	t_list	*lst;
	t_list	*node;
	char	*content;
	char	*target;
	char	*token;

	lst = ft_lstnew(ft_strtrim(input, " "));
	node = lst;
	while (node != NULL)
	{
		content = node->content;
		target = ft_next_token(content);
		if (target != NULL)
		{
			ft_istoken(target, &token);
			ft_lstinsert(node, ft_lstnew(token));
			ft_lstinsert(
				node->next, ft_lstnew(ft_strdup(target + ft_strlen(token))));
			ft_lst_replace_content(
				node, ft_substr(node->content, 0, target - content));
			node = node->next;
		}
		node = node->next;
	}
	return (ft_lstdelempty(&lst));
}

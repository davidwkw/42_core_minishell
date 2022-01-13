/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:32:45 by weng              #+#    #+#             */
/*   Updated: 2022/01/13 14:39:09 by weng             ###   ########.fr       */
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
	const char	*substr[] = {"<<", ">>", "||", "&&", " ", "<", ">", "|",
							 "(", ")"};
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
if no special token is found. Special token cannot occur at the part of
a string which is enclosed within quote (') or double quote (");
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

/* Auxiliary function that adds one token to 'lst' at each call. */
static t_list	*ft_tokenise_aux(char *input, t_list *lst)
{
	int		len;
	char	*token;
	char	*end;

	while (*input == ' ')
		input++;
	if (*input == '\0')
		return (lst);
	end = ft_next_token(input);
	if (ft_istoken(input, &token) == 0)
		token = ft_substr(input, 0, end - input);
	ft_lstadd_back(&lst, ft_lstnew(strdup(token)));
	len = ft_strlen(token);
	free(token);
	return (ft_tokenise_aux(input + len, lst));
}

/*
Tokenize the input and return a linked list, with variable expansion and
quote removal carried out.
*/
t_list	*ft_tokenise(char *input)
{
	t_list	*lst;
	t_list	*node;

	if (ft_is_well_quoted(input) == 0 || ft_is_well_bracketed(input) == 0)
		return (NULL);
	lst = ft_tokenise_aux(input, NULL);
	node = lst;
	while (node != NULL)
	{
		ft_lst_replace_content(node, ft_expand_var(node->content));
		ft_lst_replace_content(node, ft_remove_quote(node->content));
		node = node->next;
	}
	return (lst);
}

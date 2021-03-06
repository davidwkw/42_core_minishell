/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:32:45 by weng              #+#    #+#             */
/*   Updated: 2022/01/16 18:30:13 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Return 1 if substring is one of the special tokens, else return 0.

In the event 'token' is not NULL, *token will be set to the copy of the
identified token if it is found, else it will be set to NULL.

'include_space' should be set to 1 if space is to be considered a
special token.
*/
int	ft_istoken(const char *str, char **token, int include_space)
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
		if (ft_strncmp(str, substr[i], len) == 0
			&& (*substr[i] != ' ' || include_space == 1))
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
		if (quote == '\0' && ft_istoken(str, NULL, 1) == 1)
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

/* Tokenize the input and return a linked list. */
t_list	*ft_tokenise(char *input)
{
	t_list	*lst;
	char	*token;
	char	*end;

	if (ft_is_well_quoted(input) == 0 || ft_is_well_bracketed(input) == 0)
		return (NULL);
	lst = NULL;
	while (*input != '\0')
	{
		while (*input == ' ')
			input++;
		if (*input == '\0')
			break ;
		end = ft_next_token(input);
		if (ft_istoken(input, &token, 1) == 0)
			token = ft_substr(input, 0, end - input);
		ft_lstadd_back(&lst, ft_lstnew(strdup(token)));
		input += ft_strlen(token);
		free(token);
	}
	return (lst);
}

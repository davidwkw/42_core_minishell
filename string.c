/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:41:03 by weng              #+#    #+#             */
/*   Updated: 2022/01/17 16:27:46 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns a pointer to the first occurrence of the character c in the
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

/* Free 'ptr' and return 'new' */
char	*ft_strreplace(char *ptr, char *new)
{
	free(ptr);
	return (new);
}

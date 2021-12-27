/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:34:04 by weng              #+#    #+#             */
/*   Updated: 2021/12/27 23:31:58 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns pointer to the first occurence of an environment variable in
string 's', or NULL if no environment variable exists.

If name != NULL, the variable name will be pointed by *name, or NULL 
if no environment variable exists.
*/
char	*ft_findenv(char *s, char **name)
{
	char	*start;
	char	*end;
	char	*label;

	start = ft_strchr_unquoted(s, '$');
	if (*s == '\0' || start == NULL)
		label = NULL;
	else if (start[1] == '?')
		label = ft_strdup("?");
	else if (start[1] != '_' && ft_isalpha(start[1]) == 0)
		return (ft_findenv(start + 1, name));
	else
	{
		end = start + 2;
		while (*end == '_' || ft_isalnum(*end) == 1)
			end++;
		label = ft_substr(start, 1, end - start - 1);
	}
	if (name != NULL)
		*name = label;
	else
		free(label);
	return (start);
}

/* Recursive function to expand environment variable in string 's'. */
char	*ft_expand_var_aux(char *prev, char *s)
{
	char	*start;
	char	*name;
	char	*value;
	char	*temp;

	start = ft_findenv(s, &name);
	if (start == NULL)
		return (ft_strappend(prev, s));
	value = ft_getenv(name);
	temp = ft_substr(s, 0, start - s);
	s = start + ft_strlen(name) + 1;
	prev = ft_strappend(prev, temp);
	free(temp);
	free(name);
	if (value != NULL)
		prev = ft_strappend(prev, value);
	return (ft_expand_var_aux(prev, s));
}

/* Expand environment variables for in a string */
char	*ft_expand_var(char *str)
{
	return (ft_expand_var_aux(ft_strdup(""), str));
}

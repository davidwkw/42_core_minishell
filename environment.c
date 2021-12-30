/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:55:59 by weng              #+#    #+#             */
/*   Updated: 2021/12/27 13:57:11 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Get an environment variable from the g_environ global variable. Returns
a pointer to the value, or NULL if there is no match.
*/
char	*ft_getenv(const char *name)
{
	char	**env;
	int		len;

	env = g_environ;
	len = ft_strlen(name);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (&(*env)[len + 1]);
		env++;
	}
	return (NULL);
}

/*
Search through environment variables and replace. Returns non-zero if
replacement is carried out, 0 if not.
*/
static int	ft_replace_environ(char *args)
{
	char	**env;
	char	*equal;
	int		len;

	equal = ft_strchr(args, '=');
	if (equal == NULL)
		len = ft_strlen(args);
	else
		len = equal - args;
	env = g_environ;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, args, len) == 0
			&& ((*env)[len] == '=' || (*env)[len] == '\0'))
		{
			if (equal != NULL)
			{
				free(*env);
				*env = strdup(args);
			}
			return (len);
		}
		env++;
	}
	return (0);
}

/*
Returns 1 'name' is a valid name for an environment variable, else 0.

The name must be "?", or the first character of the name must be one of
'_' or alphabet. The rest of the name must be '_' or alphanumeric.
*/
static int	ft_name_valid(const char *name)
{
	if (ft_strncmp(name, "?", 2) == 0)
		return (1);
	else if (*name == '_' || ft_isalpha(*name) == 1)
		name++;
	else
		return (0);
	while (*name == '_' || ft_isalnum(*name) == 1)
		name++;
	if (*name == '\0')
		return (1);
	else
		return (0);
}

/*
Change or add an environment variable. Argument 'string' is of the form
name=value. If 'name' does not already exist in the environment, then
'string' is added to the environment. If 'name' does exist, then the
value of 'name' in the environment is change to 'value'.

if 'string' is of the form 'name', then it is added to g_environ but
only considered marked for export.

Returns zero upon success, or non-zero upon failure.
*/
int	ft_putenv(char *string)
{
	char	*equal;
	char	*name;
	int		valid;

	equal = ft_strchr(string, '=');
	if (equal != NULL)
		name = ft_substr(string, 0, equal - string);
	else
		name = ft_strdup(string);
	valid = ft_name_valid(name);
	free(name);
	if (valid == 0)
		return (EXIT_FAILURE);
	if (ft_replace_environ(string) == 0)
		return (ft_meminsert(&g_environ, string));
	else
		return (EXIT_SUCCESS);
}

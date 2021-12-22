/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:55:59 by weng              #+#    #+#             */
/*   Updated: 2021/12/22 10:13:44 by weng             ###   ########.fr       */
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
Change or add an environment variable. Argument 'string' is of the form
name=value. If 'name' does not already exist in the environment, then
'string' is added to the environment. If 'name' does exist, then the
value of 'name' in the environment is change to 'value'.

if 'string' is of the form 'name', then it is added to g_environ but
only considered marked for export.
*/
int	ft_putenv(char *string)
{
	if (ft_replace_environ(string) == 0)
		return (ft_meminsert(&g_environ, string));
	else
		return (0);
}

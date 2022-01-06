/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/30 15:17:35 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Removes the corresponding environment variable for the NAME given. */
static void	ft_unset_one(char *name)
{
	int		len;
	char	**env;

	len = ft_strlen(name);
	env = g_global.environ_vars;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, name, len) == 0
			&& ((*env)[len] == '=' || (*env)[len] == '\0'))
		{
			free(*env);
			while (env[1] != NULL)
			{
				env[0] = env[1];
				env++;
			}
			*env = NULL;
		}
		else
			env++;
	}
}

/*
Removes the corresponding environment variable for each NAME given.

The environment variables are removed by freeing the corresponding
entry from g_global.environ_vars global variable for each NAME. However, this
implementation is not thread safe, since no lock is used.

It is not possible to unset the '?' variable.

The exit status is always 0, since we are not implemanting 'readonly'
feature.
*/
int	ft_unset(char **args)
{
	while (*(++args) != NULL)
	{
		if (ft_strncmp(*args, "?", 2) == 0)
			continue ;
		ft_unset_one(*args);
	}
	return (EXIT_SUCCESS);
}

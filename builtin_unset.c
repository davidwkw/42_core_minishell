/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/20 17:41:13 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Removes the corresponding environment variable for each NAME given.

The environment variables are removed by freeing the corresponding
entry from g_environ global variable for each NAME. However, this
implementation is not thread safe, since no lock is used.
*/
int	ft_unset(char **args)
{
	int		len;
	char	**env;

	while (*(++args) != NULL)
	{
		len = ft_strlen(*args);
		env = g_environ;
		while (*env != NULL)
		{
			if (ft_strncmp(*env, *args, len) == 0
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
	return (1);
}

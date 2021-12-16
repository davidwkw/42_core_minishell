/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/16 15:56:29 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

/*
Removes the corresponding environment variable for each NAME given.

The environment variables are removed by deleteing the corresponding
entry from environ global variable for each NAME. However, this
implementation is not thread safe, since no lock is used.
*/
int	ft_unset(char **args)
{
	int		len;
	char	**env;

	args++;
	while (*args != NULL)
	{
		len = ft_strlen(*args);
		env = environ;
		while (*env != NULL)
		{
			if (ft_strncmp(*env, *args, len) == 0 && (*env)[len] == '=')
			{
				while (*env != NULL)
				{
					env[0] = env[1];
					env++;
				}
				break ;
			}
			env++;
		}
		args++;
	}
	return (1);
}

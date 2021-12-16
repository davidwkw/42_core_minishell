/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/16 15:52:21 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

/*
Run a program in a modified environment.

Since this program does not accept any option or argument, it simplifies
to printing all the environment variables.
*/
int	ft_env(char **args)
{
	extern int	errno;
	char		**env;

	if (args[1] != NULL)
	{
		errno = EINVAL;
		perror("env");
		exit(EXIT_FAILURE);
	}
	env = environ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (1);
}

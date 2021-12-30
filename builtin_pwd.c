/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/30 15:14:09 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Print the absolute pathname of the current working directory. Returns 0
upon success, or 1 upon failure.
*/
int	ft_pwd(char **args)
{
	char		*buf;

	(void) args;
	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	else
	{
		printf("%s\n", buf);
		free(buf);
		return (EXIT_SUCCESS);
	}
}

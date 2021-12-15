/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/15 17:36:15 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* print name of current/working directory */
int	ft_pwd(char **args)
{
	extern int	errno;
	char		*buf;
	int			retval;

	buf = NULL;
	retval = 0;
	if (args[1] != NULL)
	{
		errno = EINVAL;
		perror("pwd");
	}
	else
	{
		buf = getcwd(buf, 0);
		if (buf == NULL)
			perror("pwd");
		else
		{
			printf("%s\n", buf);
			free(buf);
			retval = 1;
		}
	}
	return (retval);
}

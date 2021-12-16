/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/16 13:07:53 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* print name of current/working directory */
int	ft_pwd(char **args)
{
	char		*buf;

	(void) args;
	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("pwd");
		return (0);
	}
	else
	{
		printf("%s\n", buf);
		free(buf);
		return (1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/15 17:17:53 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args)
{
	extern int	errno;

	if (args[1] != NULL)
	{
		errno = EINVAL;
		perror("exit");
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
}

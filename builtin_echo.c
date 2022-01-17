/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2022/01/17 14:32:57 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*.
Display a line of text.

The return code is always 0 unless a write error occurs.
*/
int	ft_echo(char **args)
{
	int	has_newline;
	int	i;

	has_newline = 1;
	i = 1;
	while (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
	{
		has_newline = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (has_newline == 1)
		printf("\n");
	return (EXIT_SUCCESS);
}

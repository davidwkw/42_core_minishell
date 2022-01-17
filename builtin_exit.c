/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2022/01/17 13:00:56 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Converts the initial portion of the string pointed to by 'nptr' to long long.
*/
static long long	ft_atoll(const char *nptr)
{
	long long	sign;
	long long	retval;

	sign = 1;
	retval = 0;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr) == 1)
	{
		retval *= 10;
		retval += *nptr - '0';
		nptr++;
	}
	return (retval * sign);
}

/*
Exit the shell with the status of n, where n is a number between 0 to
255.

If n is outside this range, the value n mod 255 is used instead. If
non-numeric argument is given, n = 2 is used instead.
*/
int	ft_exit(char **args)
{
	long long	n;
	char		*input;
	char		*str;

	if (args[1] != NULL && args[2] != NULL)
	{
		input = "1";
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (args[1] != NULL)
		input = args[1];
	else
		input = ft_getenv("?");
	n = ft_atoll(input);
	str = ft_lltoa_base(n, "0123456789");
	if (ft_strcmp(str, input) == 0)
		n = ((n % 256) + 256) % 256;
	else
	{
		n = 2;
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(input, 2);
		ft_putendl_fd(" : numeric argument required", 2);
	}
	exit(n);
}

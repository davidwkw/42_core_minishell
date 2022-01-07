/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:28:33 by weng              #+#    #+#             */
/*   Updated: 2022/01/07 11:28:48 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_environ;

/* Initialise environment variable array g_environ and ? variable. */
void	ft_init_environment(char **env)
{
	g_environ = ft_memdup((const char **) env);
	ft_putenv("?=0");
}

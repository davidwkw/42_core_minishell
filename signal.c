/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:37:17 by kwang             #+#    #+#             */
/*   Updated: 2022/01/07 14:00:00 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_rl_reprompt(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

static void	ft_proc_reprompt(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
}

void	ft_init_proc_signals(void)
{
	signal(SIGINT, ft_proc_reprompt);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_init_rl_signals(void)
{
	signal(SIGINT, ft_rl_reprompt);
	signal(SIGQUIT, SIG_IGN);
}

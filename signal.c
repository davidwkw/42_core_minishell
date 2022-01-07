/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:37:17 by kwang             #+#    #+#             */
/*   Updated: 2022/01/07 17:26:30 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Calls the signal function. Prints error message if SIG_ERR is returned. */
t_sighandler	ft_signal(int signum, t_sighandler handler)
{
	t_sighandler	retval;

	retval = signal(signum, handler);
	if (retval == SIG_ERR)
		perror("signal");
	return (retval);
}

/* (Interactive) Print a new prompt on a newline. */
static void	ft_rl_reprompt(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

/* Terminates a running program. */
static void	ft_proc_reprompt(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
}

/*
Register signal handlers used during program run.
Ctrl-C (SIGINT): Terminates the running program.
Ctrl-D (SIGQUIT): send EOF
*/
void	ft_init_proc_signals(void)
{
	ft_signal(SIGINT, ft_proc_reprompt);
	ft_signal(SIGQUIT, SIG_IGN);
}

/*
Register signal handlers used during interactive shell.
Ctrl-C (SIGINT): Print a new prompt on a newline.
Ctrl-\ (SIGQUIT): does nothing.
*/
void	ft_init_rl_signals(void)
{
	ft_signal(SIGINT, ft_rl_reprompt);
	ft_signal(SIGQUIT, SIG_IGN);
}

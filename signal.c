/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:37:17 by kwang             #+#    #+#             */
/*   Updated: 2022/01/17 11:02:12 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Calls the signal function. Prints error message if SIG_ERR is returned. */
t_shdlr	ft_signal(int signum, t_shdlr handler)
{
	t_shdlr	retval;

	retval = signal(signum, handler);
	if (retval == SIG_ERR)
		perror("signal");
	return (retval);
}

/* Print a new prompt on a new line. */
void	ft_new_prompt_line(char *str)
{
	rl_replace_line("", 0);
	if (str != NULL)
		printf("%s", str);
	printf("\n");
	rl_on_new_line();
}

/* (Interactive) Print a new prompt on a newline. */
static void	ft_sigint_handler(int signum)
{
	(void) signum;
	ft_new_prompt_line(NULL);
	rl_redisplay();
	ft_putenv("?=130");
}

/* Revert signal handlers to default handlers. */
void	ft_sighandler_default(void)
{
	ft_signal(SIGINT, SIG_DFL);
	ft_signal(SIGQUIT, SIG_DFL);
}

/*
Register signal handlers used during interactive shell.
Ctrl-C (SIGINT): Print a new prompt on a newline.
Ctrl-\ (SIGQUIT): does nothing.
*/
void	ft_sighandler_shell(void)
{
	ft_signal(SIGINT, ft_sigint_handler);
	ft_signal(SIGQUIT, SIG_IGN);
}

#include "minishell.h"

static void	reprompt(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, reprompt);
	signed(SIGQUIT, SIG_IGN);
}

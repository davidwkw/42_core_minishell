#include "minishell.h"

char	*ft_get_cwd_prompt(void)
{
	static char	*cwd_prompt = NULL;
	char		*dir;
	char		*temp;

	free(cwd_prompt);
	dir = getcwd(NULL, 0);
	temp = ft_strjoin(BOLD GREEN, dir);
	free(dir);
	dir = ft_strjoin(temp, "$ ");
	free(temp);
	cwd_prompt = ft_strjoin(dir, "\033[0m");
	free(dir);
	return (cwd_prompt);
}

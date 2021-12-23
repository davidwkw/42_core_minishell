#include "minishell.h"

/*
Creates .history file (if does not exist) 
and appends cmd with newline before writing to file.
*/
int	save_history(char *cmd)
{
	int		fd;
	char	*temp;

	fd = open(HISTORY_FILE, O_CREAT | O_WRONLY | O_APPEND);
	if (fd == -1)
		return (-1);
	temp = ft_strjoin(cmd, "\n");
	if (write(fd, temp, ft_strlen(temp)) == -1)
		return (-1);
	close(fd);
	free(temp);
	return (0);
}

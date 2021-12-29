#include "minishell.h"

/*
Creates .history file (if does not exist)
and appends cmd with newline before writing to file.
Returns 0 on success and -1 on failure.
*/
int	save_history(char *cmd)
{
	int		fd;
	char	*temp;

	fd = open(HISTORY_FILE, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR);
	if (fd == -1)
		return (-1);
	temp = ft_strjoin(cmd, "\n");
	if (write(fd, temp, ft_strlen(temp)) == -1)
		return (-1);
	close(fd);
	free(temp);
	return (0);
}

/*
Lists logged history commands from start_num until EOF.
*/
int	list_history(int start_num)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		if (i >= start_num)
			printf("%d %s\n", i, line);
		free(line);
		i++;
	}
	close(fd);
	return (i);
}

/*
Helper function for list_history. Counts total list of lines
in history file. Returns number of lines in the history file or -1 if failure.
*/
int	count_history(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		free(line);
		i++;
	}
	close(fd);
	return (i);
}

#include "minishell.h"

/*
Helper function to check if string contains only digits
*/
int	is_strdigit(char *string)
{
	while (*string)
	{
		if (!ft_isdigit(*string))
			return (0);
		string++;
	}
	return (1);
}

/*
Helper function for list_history. Counts total list of lines
in history file. Returns number of lines in the history file.
Returns -1 if there is an error opening the file.
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

/*
Helper function to retrieve line specified by the num parameter.
*/
char	*get_line_num(int fd, int num)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < num)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		free(line);
	}
	line = get_next_line(fd);
	return (line);
}

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
	int		hist_count;

	fd = open(HISTORY_FILE, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR);
	if (fd == -1)
		return (-1);
	hist_count = count_history();
	temp = get_line_num(fd, hist_count);
	if (strncmp(cmd, temp, ft_strlen(cmd)))
	{
		free(temp);
		temp = ft_strjoin(cmd, "\n");
		if (write(fd, temp, ft_strlen(temp)) == -1)
			return (-1);
	}
	close(fd);
	free(temp);
	return (0);
}

/*
Lists logged history commands from start_num until EOF.
Returns number of lines printed. If number of lines returned is less than
actual total number of history lines, an error in getting next line has occured.
Returns -1 if there is an error opening the file.
*/
static int	list_history(int start_num)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		if (i >= start_num)
			printf("%d %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	return (i);
}

/*
Primary function for history. Takes the command 'history <option>'.
history command without an options lists the last <HISTORY_COUNT> amount of commands.
history -c clears the history file.
history <num> list the last <num> amount of commands
*/
int	ft_history(char **args)
{
	int	fd;
	int	total_hist_count;
	int	min_hist_count;
	int	num_input;

	total_hist_count = count_history();
	min_hist_count = total_hist_count - HISTORY_COUNT;
	if (min_hist_count < 1)
		min_hist_count = 1;
	if (args[1] == NULL)
		list_history(min_hist_count);
	else if (!ft_strncmp(args[1], "-c", 2))
	{
		unlink(HISTORY_FILE);
		rl_clear_history();
		fd = open(HISTORY_FILE, O_CREAT | O_WRONLY, S_IWUSR);
		close(fd);
	}
	else if (is_strdigit(args[1]))
	{
		num_input = atoi(args[1]);
		if (num_input < total_hist_count)
			min_hist_count = total_hist_count - num_input;
		list_history(min_hist_count);
	}
	return (0);
}

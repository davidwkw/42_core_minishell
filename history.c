/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:12 by kwang             #+#    #+#             */
/*   Updated: 2022/01/05 22:04:00 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Appends 'cmd' as a new line into .history if it is different from the
last line. The file '.history' will be created if it does not exist.
*/
void	save_history(char *cmd)
{
	int		fd;
	int		hist_count;
	char	*last_line;

	fd = ft_open(HISTORY_FILE, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return ;
	hist_count = count_history();
	if (hist_count == 0)
		last_line = NULL;
	else
		last_line = get_line_num(fd, hist_count);
	if (last_line == NULL || (is_strwhitespace(cmd) != 1
			&& ft_strncmp(last_line, cmd, ft_strlen(cmd) + 1) != 0))
	{
		add_history(cmd);
		ft_putstr_fd(cmd, fd);
		ft_putchar_fd('\n', fd);
	}
	free(last_line);
	ft_close(fd);
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

	fd = ft_open(HISTORY_FILE, O_RDONLY, 0);
	if (fd == -1)
		return (-1);
	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (i >= start_num)
			printf("%d %s", i, line);
		free(line);
		i++;
	}
	ft_close(fd);
	return (i);
}

/*
Primary function for history. Takes the command 'history <option>'.
history command without an options lists the last <HISTORY_COUNT> amount
of commands.
history -c clears the history file.
history <num> list the last <num> amount of commands
*/
int	ft_history(char **args)
{
	int	total_hist_count;
	int	min_hist_count;
	int	num_input;

	total_hist_count = count_history();
	min_hist_count = total_hist_count - HISTORY_COUNT + 1;
	if (min_hist_count < 1)
		min_hist_count = 1;
	if (args[1] == NULL)
		list_history(min_hist_count);
	else if (!ft_strncmp(args[1], "-c", 2))
	{
		unlink(HISTORY_FILE);
		rl_clear_history();
		ft_close(ft_open(HISTORY_FILE, O_CREAT | O_WRONLY, S_IWUSR));
	}
	else if (is_strdigit(args[1]))
	{
		num_input = atoi(args[1]);
		if (num_input < total_hist_count)
			min_hist_count = total_hist_count - num_input + 1;
		list_history(min_hist_count);
	}
	return (0);
}

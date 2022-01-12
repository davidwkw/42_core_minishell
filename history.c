/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:12 by kwang             #+#    #+#             */
/*   Updated: 2022/01/12 09:13:40 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Appends 'cmd' as a new line into .history if it is different from the
last line. The file '.history' will be created if it does not exist.
*/
void	ft_history_save(char *cmd)
{
	int		fd;
	char	*last;
	char	*new;

	if (*cmd == ' ')
		return ;
	fd = ft_open(HISTORY_FILE, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return ;
	last = ft_get_last_line(HISTORY_FILE);
	if (last == NULL || ft_strncmp(last, cmd, ft_strlen(cmd) + 1) != 0)
	{
		new = ft_strtrim(cmd, " ");
		add_history(new);
		ft_putendl_fd(new, fd);
		free(new);
	}
	free(last);
	ft_close(fd);
}

/*
Lists logged history commands from start_num until EOF.
Returns number of lines printed. If number of lines returned is less than
actual total number of history lines, an error in getting next line has occured.
Returns -1 if there is an error opening the file.
*/
static int	ft_history_list(int start_num)
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

	total_hist_count = ft_count_line(HISTORY_FILE);
	min_hist_count = total_hist_count - HISTORY_COUNT + 1;
	if (min_hist_count < 1)
		min_hist_count = 1;
	if (args[1] == NULL)
		ft_history_list(min_hist_count);
	else if (ft_strncmp(args[1], "-c", 3) == 0)
	{
		unlink(HISTORY_FILE);
		rl_clear_history();
		ft_close(ft_open(HISTORY_FILE, O_CREAT | O_WRONLY, S_IWUSR));
	}
	else if (ft_isdigit_str(args[1]) == 1)
	{
		num_input = ft_atoi(args[1]);
		if (num_input < total_hist_count)
			min_hist_count = total_hist_count - num_input + 1;
		ft_history_list(min_hist_count);
	}
	return (0);
}

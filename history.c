/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:12 by kwang             #+#    #+#             */
/*   Updated: 2022/01/15 16:13:09 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Clears the history file. */
static int	ft_history_delete(void)
{
	unlink(ft_get_history_file());
	rl_clear_history();
	ft_close(ft_open(ft_get_history_file(), O_CREAT | O_WRONLY, S_IWUSR));
	return (EXIT_SUCCESS);
}

/*
Lists the last 'n' logged history commands from HISTORY_FILE. If 'n' is
greater than the actual number of lines logged, only the lines logged
will be printed. If 'n' is -1, the last HISTORY_COUNT lines of commands
will be printed.
*/
static int	ft_history_list(int n)
{
	int		count;
	int		i;
	int		fd;
	char	*line;

	if (n == -1)
		n = HISTORY_COUNT;
	count = ft_count_line(ft_get_history_file());
	if (n > count)
		n = count;
	fd = ft_open(ft_get_history_file(), O_RDONLY, 0);
	if (fd == -1)
		return (EXIT_FAILURE);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (++i >= count - n + 1)
			printf("%d %s", i, line);
		free(line);
		line = get_next_line(fd);
	}
	ft_close(fd);
	return (EXIT_SUCCESS);
}

/* Prints the history error message. */
static int	ft_history_error(char *option)
{
	if (option != NULL)
	{
		ft_putstr_fd("minishell: history: ", 2);
		ft_putstr_fd(option, 2);
		ft_putendl_fd(": invalid option", 2);
	}
	ft_putendl_fd("history: usage history [-c] [n]", 2);
	return (EXIT_FAILURE);
}

/*
Getter function to obtain absolute history file path.
Returns a malloc-ed string of the history file path.
*/
char	*ft_get_history_file(void)
{
	static char	*history_file = NULL;
	char		*temp;
	char		*dir;

	if (history_file == NULL)
	{
		dir = getcwd(NULL, 0);
		temp = ft_strjoin(dir, "/");
		free(dir);
		history_file = ft_strjoin(temp, HISTORY_FILE);
		free(temp);
	}
	return (history_file);
}

/*
List or clear minishell history.

Take the parameters 'history [-c] [n]', such that
	history:	list the last HISTORY_COUNT lines of commands.
	history -c:	clears the history file.
	history n:	list the last n lines of commands.
*/
int	ft_history(char **args)
{
	if (args[1] == NULL)
		return (ft_history_list(-1));
	else if (ft_arrsize(args) > 3)
		return (ft_history_error(NULL));
	else if (ft_strcmp(args[1], "-c") == 0)
	{
		if (args[2] == NULL || ft_isdigit_str(args[2]) == 1)
			return (ft_history_delete());
		else
			return (ft_history_error(args[2]));
	}
	else if (ft_isdigit_str(args[1]) == 1)
	{
		if (args[2] == NULL)
			return (ft_history_list(ft_atoi(args[1])));
		else
			return (ft_history_error(args[2]));
	}
	return (ft_history_error(args[1]));
}

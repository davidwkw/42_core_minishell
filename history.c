/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:19:12 by kwang             #+#    #+#             */
/*   Updated: 2022/01/12 11:12:30 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns 1 if string 'str' only contains digits, 0 otherwise. */
int	ft_isdigit_str(const char *str)
{
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

/* Clears the history file. */
static int	ft_history_delete(void)
{
	unlink(HISTORY_FILE);
	rl_clear_history();
	ft_close(ft_open(HISTORY_FILE, O_CREAT | O_WRONLY, S_IWUSR));
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
	count = ft_count_line(HISTORY_FILE);
	if (n > count)
		n = count;
	fd = ft_open(HISTORY_FILE, O_RDONLY, 0);
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
	else if (ft_strncmp(args[1], "-c", 3) == 0)
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

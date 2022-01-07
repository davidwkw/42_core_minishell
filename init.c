/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:28:33 by weng              #+#    #+#             */
/*   Updated: 2022/01/07 12:01:35 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_environ;

/* Initialise environment variable array g_environ and ? variable. */
void	ft_init_environment(char **env)
{
	g_environ = ft_memdup((const char **) env);
	ft_putenv("?=0");
}

/* Initializes history from HISTORY_FILE. */
void	ft_init_history(void)
{
	int		fd;
	char	*line;

	fd = ft_open(HISTORY_FILE, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = ft_strip_newline(line);
		add_history(line);
		free(line);
		line = get_next_line(fd);
	}
	ft_close(fd);
}

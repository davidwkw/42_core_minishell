/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:17:38 by kwang             #+#    #+#             */
/*   Updated: 2022/01/17 16:00:37 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Set and return the absolute history file path, which is
	<directory where minishell is called from>/<HISTORY_FILE>
*/
char	*ft_get_history_file(void)
{
	static char	*history_file = NULL;
	char		*dir;

	if (history_file == NULL)
	{
		dir = getcwd(NULL, 0);
		history_file = ft_pathjoin(dir, HISTORY_FILE);
		free(dir);
	}
	return (history_file);
}

/*
Returns the number of lines in the file 'pathname', or -1 if there is an
error when opening the file.
*/
int	ft_count_line(const char *pathname)
{
	int		fd;
	char	*line;
	int		i;

	fd = ft_open(pathname, O_RDONLY, 0);
	if (fd == -1)
		return (-1);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	ft_close(fd);
	return (i);
}

/* Remove the trailing '\'n' from 'str'. The original 'str' is free. */
char	*ft_strip_newline(char *str)
{
	int		len;
	char	*retval;

	len = ft_strlen(str);
	if (str[len - 1] == '\n')
	{
		retval = ft_substr(str, 0, len - 1);
		free(str);
		return (retval);
	}
	else
		return (str);
}

/*
Helper function to retrieve the last line of a file given by 'pathname'.
The trailing '\n' character is removed from the return value.
*/
char	*ft_get_last_line(const char *pathname)
{
	int		fd;
	char	*line;
	char	*next;

	fd = ft_open(pathname, O_RDONLY, 0);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	if (line != NULL)
		next = get_next_line(fd);
	else
		next = NULL;
	while (next != NULL)
	{
		free(line);
		line = next;
		next = get_next_line(fd);
	}
	ft_close(fd);
	if (line != NULL)
		return (ft_strip_newline(line));
	else
		return (NULL);
}

/*
Appends 'cmd' as a new line into .history if it is different from the
last line. The file '.history' will be created if it does not exist.
*/
void	ft_history_save(char *cmd)
{
	int		fd;
	char	*last;
	char	*new;
	char	*history_file;

	if (*cmd == ' ')
		return ;
	history_file = ft_get_history_file();
	fd = ft_open(history_file, O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return ;
	last = ft_get_last_line(history_file);
	if (last == NULL || ft_strcmp(last, cmd) != 0)
	{
		new = ft_strtrim(cmd, " ");
		add_history(new);
		ft_putendl_fd(new, fd);
		free(new);
	}
	free(last);
	ft_close(fd);
}

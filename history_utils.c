/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:17:38 by kwang             #+#    #+#             */
/*   Updated: 2022/01/05 17:44:40 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Helper function to check if string contains only digits.
Returns 1 if str only contains digits, 0 otherwise.
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
Helper function to check if string contains only whitespace.
Returns 1 if str only contains whitespace, 0 otherwise.
*/
int	is_strwhitespace(char *string)
{
	while (*string)
	{
		if (!ft_isspace(*string))
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

	fd = ft_open(HISTORY_FILE, O_RDONLY, 0);
	if (fd == -1)
		return (-1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
		i++;
	}
	ft_close(fd);
	return (i);
}

/*
Helper function to retrieve line specified by the num parameter.
The trailing '\n' character is removed from the return value.
*/
char	*get_line_num(int fd, int num)
{
	int		i;
	int		len;
	char	*line;
	char	*retval;

	i = -1;
	while (++i < num - 1)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		free(line);
	}
	line = get_next_line(fd);
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
	{
		retval = ft_substr(line, 0, len - 1);
		free(line);
		return (retval);
	}
	else
		return (line);
}

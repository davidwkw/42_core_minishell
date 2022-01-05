/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:57:41 by weng              #+#    #+#             */
/*   Updated: 2022/01/06 00:08:57 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Write warning to stderr when here_document is delimited by end-of-file */
static void	ft_eof_warning(char *delimiter)
{
	ft_putstr_fd("warning: here-document delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("'))", 2);
}

/*
Opens the HEREDOC_FILE and writes the content from stdin to it, line
by line.

A warning is raised if the EOF is detected.
*/
void	ft_write_heredoc(char *delimiter)
{
	int			fd;
	char		*line;

	fd = ft_open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL && (ft_strlen(line) - 1 != ft_strlen(delimiter)
			|| ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0))
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (line == NULL)
		ft_eof_warning(delimiter);
	free(line);
	ft_close(fd);
}

/* Opens the input file and returns the file descriptor. */
int	open_infile(t_cmd *cmd)
{
	char	*infile;

	if (cmd->heredoc == 1)
		infile = HEREDOC_FILE;
	else
		infile = cmd->infile;
	return (ft_open(infile, O_RDONLY, 0));
}

/*
Opens the 'outfile', if exists; or creates the output file, if not.
If infile == HEREDOC_FILE, newlines are appended to the end of the file
rather than overwriting the original content.
*/
int	open_outfile(t_cmd *cmd)
{
	if (cmd->outfile == NULL)
		return (-1);
	if (cmd->append == 1)
		return (ft_open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR));
	else
		return (ft_open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR));
}

/* Saves or restores the stdin and stdout file numbers. */
void	ft_save_restore_fd(void)
{
	static int	in = -1;
	static int	out = -1;

	if (in == -1)
	{
		in = ft_dup(STDIN_FILENO);
		out = ft_dup(STDOUT_FILENO);
	}
	else
	{
		ft_pipe_dup_close(in, STDIN_FILENO);
		ft_pipe_dup_close(out, STDOUT_FILENO);
		in = -1;
		out = -1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:57:41 by weng              #+#    #+#             */
/*   Updated: 2022/01/19 01:21:55 by weng             ###   ########.fr       */
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
int	ft_write_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = ft_open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (-1);
	line = readline("> ");
	while (line != NULL && ft_strcmp(line, delimiter) != 0)
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	if (line == NULL)
		ft_eof_warning(delimiter);
	free(line);
	return (ft_close(fd));
}

/*
Returns the file descriptor to the last input file of a simple command,
or -1 if an error occurs. All other output files in the list will be
opened and closed in sequence, with heredocument handled appropriately.
*/
int	ft_open_infile(t_scmd *scmd, int fd)
{
	t_list	*node;
	t_inout	*inout;

	node = scmd->infile;
	while (node != NULL)
	{
		inout = node->content;
		if (fd >= 0)
			ft_close(fd);
		fd = -1;
		if (inout->type == SINGLE)
			fd = ft_open(inout->filename, O_RDONLY, 0);
		else if (inout->type == DOUBLE)
			fd = ft_open(HEREDOC_FILE, O_RDONLY, 0);
		else
			ft_putstr_fd("ft_open_infile: unknown in/out type", 2);
		if (fd == -1)
			return (-1);
		node = node->next;
	}
	return (fd);
}

/*
Returns the file descriptor to the last output file of a simple command,
or -1 if an error occurs. All other output files in the list will be
opened and closed in sequence.
*/
int	ft_open_outfile(t_scmd *scmd, int fd)
{
	t_list	*node;
	t_inout	*inout;

	node = scmd->outfile;
	while (node != NULL)
	{
		inout = node->content;
		if (fd >= 0)
			ft_close(fd);
		fd = -1;
		if (inout->type == SINGLE)
			fd = ft_open(
					inout->filename, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR);
		else if (inout->type == DOUBLE)
			fd = ft_open(
					inout->filename, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR);
		else
			ft_putstr_fd("ft_open_outfile: unknown in/out type", 2);
		if (fd == -1)
			return (-1);
		node = node->next;
	}
	return (fd);
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

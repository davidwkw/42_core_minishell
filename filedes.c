/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:45:22 by weng              #+#    #+#             */
/*   Updated: 2022/01/03 14:52:38 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create pipe. Returns 0 upon failure or -1 upon success. */
int	ft_pipe_create(int fd[2])
{
	int	retval;

	retval = pipe(fd);
	if (retval == -1)
		perror("pipe");
	return (retval);
}

/*
Duplicate a file descriptor to a new one, and close the old one. Returns
the newfd upon success, or -1 upon failure.
*/
int	ft_pipe_dup_close(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		return (-1);
	}
	ft_close(oldfd);
	return (newfd);
}

/*
Open a file and return a file descriptor, or -1 upon failure.

'mode' must be supplied whne O_CREAT or O_TMPFILE is specified, else it
is ignored.
*/
int	ft_open(const char *pathname, int flags, mode_t mode)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd == -1)
	{
		ft_putstr_fd("open: ", 2);
		perror(pathname);
	}
	return (fd);
}

/* Close a file descriptor. Returns 0 upon success, or -1 upon failure. */
int	ft_close(int fd)
{
	int	retval;

	retval = close(fd);
	if (retval == -1)
		perror("close");
	return (retval);
}

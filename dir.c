/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:12:38 by weng              #+#    #+#             */
/*   Updated: 2022/01/14 13:42:38 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Opens a directory. Prints error message if error is encountered. */
DIR	*ft_opendir(const char *name)
{
	DIR	*dirp;

	dirp = opendir(name);
	if (dirp == NULL)
		perror("opendir");
	return (dirp);
}

/* Closes a directory. Prints error message if error is encountered. */
int	ft_closedir(DIR *dirp)
{
	int	retval;

	retval = closedir(dirp);
	if (retval == -1)
		perror("closedir");
	return (retval);
}

/* Read a directory. Prints error message if error is encountered. */
static t_dirent	*ft_readdir(DIR *dirp)
{
	extern int	errno;
	t_dirent	*dirent;

	errno = 0;
	dirent = readdir(dirp);
	if (errno != 0)
		perror("readdir");
	return (dirent);
}

/*
Lists all content within the directory 'dir'. If 'hidden' is 0, only
return non-hidden files, otherwise only return hidden files.
*/
t_list	*ft_ls(const char *dir, char hidden)
{
	DIR			*dirp;
	t_dirent	*dirent;
	t_list		*lst;
	char		*name;

	lst = NULL;
	dirp = ft_opendir(dir);
	if (dirp == NULL)
		return (NULL);
	dirent = ft_readdir(dirp);
	while (dirent != NULL)
	{
		name = dirent->d_name;
		if ((*name == '.') == (hidden != 0))
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(name)));
		dirent = ft_readdir(dirp);
	}
	ft_closedir(dirp);
	return (lst);
}

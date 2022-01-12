/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:12:38 by weng              #+#    #+#             */
/*   Updated: 2022/01/12 13:12:52 by weng             ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/21 11:04:01 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Parse the input directory, with support for '~' symbol. The default
directory is the value of the HOME environment variable.
*/
static char	*ft_parse_dir(char *path)
{
	char	*retval;
	char	*home;

	home = ft_getenv("HOME");
	if (home == NULL)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		exit(EXIT_FAILURE);
	}
	if (path == NULL || ft_strncmp(path, "~", 2) == 0)
		retval = ft_strdup(home);
	else if (ft_strncmp(path, "~/", 2) == 0)
		retval = ft_strjoin(home, path + 1);
	else
		retval = ft_strdup(path);
	return (retval);
}

/*
Change the working directory. The default directory is the value of the
HOME environment variable.
*/
int	ft_cd(char **args)
{
	char	*str;
	char	*path;

	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		exit(EXIT_FAILURE);
	}
	path = ft_parse_dir(args[1]);
	if (chdir(path) == -1)
	{
		str = ft_strjoin("cd: ", path);
		perror(str);
		free(str);
		free(path);
		exit(EXIT_FAILURE);
	}
	else
	{
		free(path);
		return (1);
	}
}

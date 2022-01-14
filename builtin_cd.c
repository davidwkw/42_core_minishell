/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2022/01/14 14:58:22 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
If 'path' is NULL, returns the HOME directory; else if 'path' == "~" or
'path' begins with "~/", ~ will be replace by the home directory; else
return 'path' unaltered.

Returns NULL if HOME environment variable is not set, else the amended
'path'.
*/
static char	*ft_parse_dir(char *path)
{
	char	*home;

	if (path != NULL && *path != '~')
		return (ft_strdup(path));
	home = ft_getenv("HOME");
	if (home == NULL)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (NULL);
	}
	if (path == NULL || ft_strcmp(path, "~") == 0)
		return (ft_strdup(home));
	else
		return (ft_strjoin(home, path + 1));
}

/*
Change the working directory. The default directory is the value of the
HOME environment variable. Returns 0 upon success, or 1 upon failure.
*/
int	ft_cd(char **args)
{
	char	*str;
	char	*path;

	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	path = ft_parse_dir(args[1]);
	if (path == NULL)
		return (EXIT_FAILURE);
	else if (chdir(path) == -1)
	{
		str = ft_strjoin("cd: ", path);
		perror(str);
		free(str);
		free(path);
		return (EXIT_FAILURE);
	}
	else
	{
		free(path);
		return (EXIT_SUCCESS);
	}
}

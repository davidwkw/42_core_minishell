/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/21 13:59:22 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Display a list of all exported variables and functions.

Exclusion from the export list:
'_' : the last command
'?' : the last exit status
*/
static void	ft_display_list(void)
{
	char	**env;
	char	**cpy;
	char	*equal;
	char	*name;

	env = ft_memdup((const char **) g_environ);
	ft_memsort(env);
	cpy = env;
	while (*env != NULL)
	{
		equal = ft_strchr(*env, '=');
		if (equal == NULL)
			printf("declare -x %s\n", *env);
		else
		{
			name = ft_substr(*env, 0, equal - *env);
			if (ft_strncmp(name, "_", 2) != 0 && ft_strncmp(name, "?", 2) != 0)
				printf("declare -x %s=\"%s\"\n", name, equal + 1);
			free(name);
		}
		env++;
	}
	ft_memdel(cpy);
}

/*
Set export attribute for shell variables, or display a list of all
exported variables and functions

Marks each NAME for automatic export to the environment of subsequently
executed commands. If VALUE is supplied, assign VALUE before exporting.

A variable without value is considered set by adding it to the
g_environ with "NAME" only.
*/
int	ft_export(char **args)
{
	if (args[1] == NULL)
		ft_display_list();
	else
	{
		while (*(++args) != NULL)
			ft_putenv(*args);
	}
	return (1);
}

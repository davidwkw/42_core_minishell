/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:50:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/20 17:02:55 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Sort a null-terminated array of strings using insertion sort. */
static void	ft_memsort(char **arr)
{
	char	*key;
	int		len;
	int		i;
	int		j;

	len = ft_memsize((const char **) arr);
	j = 1;
	while (j < len)
	{
		key = arr[j];
		i = j - 1;
		while (i >= 0
			&& ft_strncmp(arr[i], key, ft_strlen(arr[i] + 1)) > 0)
		{
			arr[i + 1] = arr[i];
			i--;
		}
		arr[i + 1] = key;
		j++;
	}
}

/*
Display a list of all exported variables and functions.

The variable '_' stores the	last command and is excluded from the export
list.
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
			if (ft_strncmp(name, "_", 2) != 0)
				printf("declare -x %s=\"%s\"\n", name, equal + 1);
			free(name);
		}
		env++;
	}
	ft_memdel(cpy);
}

/*
Search through environment variables and replace. Returns non-zero if
replacement is carried out, 0 if not.
*/
int	ft_replace_environ(char *args)
{
	char	**env;
	char	*equal;
	int		len;

	equal = ft_strchr(args, '=');
	if (equal == NULL)
		len = ft_strlen(args);
	else
		len = equal - args;
	env = g_environ;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, args, len) == 0
			&& ((*env)[len] == '=' || (*env)[len] == '\0'))
		{
			if (equal != NULL)
			{
				free(*env);
				*env = strdup(args);
			}
			return (len);
		}
		env++;
	}
	return (0);
}

/* Insert a new line in g_environ */
static void	ft_insert_environ(char *args)
{
	ssize_t	size;

	size = ft_memsize((const char **) g_environ);
	g_environ = ft_memresize(g_environ, size + 1);
	g_environ[size] = ft_strdup(args);
	if (g_environ[size] == NULL)
	{
		perror("ft_insert_environ");
		exit(EXIT_FAILURE);
	}
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
		{
			if (ft_replace_environ(*args) == 0)
				ft_insert_environ(*args);
		}
	}
	return (1);
}

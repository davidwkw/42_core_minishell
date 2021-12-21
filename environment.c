/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:42:03 by weng              #+#    #+#             */
/*   Updated: 2021/12/21 11:08:40 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the size of a null-terminated array of pointers. */
size_t	ft_memsize(const char **arr)
{
	size_t	retval;
	char	**cpy;

	cpy = (char **) arr;
	retval = 0;
	while (*cpy++ != NULL)
		retval++;
	return (retval);
}

/* Duplicates a null-terminated array of pointers. */
char	**ft_memdup(const char **arr)
{
	size_t	size;
	char	**retval;

	if (arr == NULL)
		return (NULL);
	size = ft_memsize(arr);
	retval = ft_calloc(sizeof(char *), size + 1);
	if (retval != NULL)
	{
		while (size-- > 0)
			retval[size] = ft_strdup(arr[size]);
	}
	return (retval);
}

/* Resize a null-terminated array of pointers. */
char	**ft_memresize(char **arr, size_t size)
{
	char	**retval;
	size_t	size_o;
	size_t	i;

	if (arr == NULL)
		return (NULL);
	size_o = ft_memsize((const char **) arr);
	if (size_o < size)
	{
		retval = ft_calloc(sizeof(char *), size + 1);
		if (retval != NULL)
			ft_memcpy(retval, arr, sizeof(char *) * size_o);
		free(arr);
		return (retval);
	}
	else
	{
		printf("size = %ld, size_o = %ld\n", size, size_o);
		i = size;
		while (i < size_o)
			free(arr[i++]);
		return (arr);
	}
}

/* Free memories associated with a null-terminated array of pointers. */
void	ft_memdel(char **arr)
{
	char	**cpy;

	if (arr == NULL)
		return ;
	cpy = arr;
	while (*arr != NULL)
		free(*arr++);
	free(cpy);
}

/*
Get an environment variable from the g_environ global variable. Returns
a pointer to the value, or NULL if there is no match.
*/
char	*ft_getenv(const char *name)
{
	char	**env;
	int		len;

	env = g_environ;
	len = ft_strlen(name);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (&(*env)[len + 1]);
		env++;
	}
	return (NULL);
}

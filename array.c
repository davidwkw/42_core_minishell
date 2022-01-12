/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:42:03 by weng              #+#    #+#             */
/*   Updated: 2022/01/12 12:04:12 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the size of a null-terminated array of pointers. */
size_t	ft_arrsize(const void *arr)
{
	const void	**array;
	size_t		retval;

	array = (const void **) arr;
	retval = 0;
	while (array[retval] != NULL)
		retval++;
	return (retval);
}

/*
Duplicates a null-terminated array of pointers 'arr' with function
'func' to duplicate the content of each entry in the arary.
*/
void	*ft_arrdup(const void *arr, void *(*func)(const void *))
{
	void	**array;
	void	**retval;
	size_t	size;

	if (arr == NULL)
		return (NULL);
	array = (void **) arr;
	size = ft_arrsize(array);
	retval = ft_calloc(sizeof(char *), size + 1);
	if (retval != NULL)
	{
		while (size-- > 0)
			retval[size] = func(array[size]);
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
	size_o = ft_arrsize(arr);
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
Insert a string at the back of a null-terminated array of strings.
'dest' is the address of the array, while 'str' is the string to be
inserted. Returns 0 upon success, or non-zero upon failure.
*/
int	ft_meminsert(char ***dest, char *str)
{
	extern int	errno;
	char		**arr;
	ssize_t		size;

	arr = *dest;
	size = ft_arrsize(arr);
	arr = ft_memresize(arr, size + 1);
	if (arr == NULL)
	{
		errno = ENOMEM;
		perror("memeresize");
		return (EXIT_FAILURE);
	}
	arr[size] = ft_strdup(str);
	if (arr[size] == NULL)
	{
		errno = ENOMEM;
		perror("ft_meminsert");
		return (EXIT_FAILURE);
	}
	*dest = arr;
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:42:03 by weng              #+#    #+#             */
/*   Updated: 2022/01/12 12:53:37 by weng             ###   ########.fr       */
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

/*
Resize a null-terminated array of pointers 'arr' to the new size 'size'.
If required, the memory of the element's content will be freed using the
function 'del'.
*/
void	*ft_arr_resize(void *arr, size_t size, void (*del)(void *))
{
	void	**retval;
	size_t	size_o;
	size_t	i;

	if (arr == NULL)
		return (NULL);
	size_o = ft_arrsize(arr);
	if (size_o < size)
	{
		retval = ft_calloc(sizeof(void *), size + 1);
		if (retval == NULL)
			perror("ft_arr_resize");
		else if (retval != NULL)
			ft_memcpy(retval, arr, sizeof(void *) * size_o);
		free(arr);
		return (retval);
	}
	else
	{
		i = size;
		while (i < size_o)
			del(((void **) arr)[i++]);
		return (arr);
	}
}

/*
Free memories associated with a null-terminated array of pointers. The
memory of the element's content will be freed using the function 'del'.
*/
void	ft_arrclear(void *arr, void (*del)(void *))
{
	void	**array;

	if (arr == NULL)
		return ;
	array = arr;
	while (*array != NULL)
		del(*array++);
	free(arr);
}

/*
Insert a pointer 'ptr' to the back of a null-terminated array of
pointers 'arr'. Returns 0 upon success, or non-zero upon failure.
*/
int	ft_arradd_back(void *arr, void *ptr)
{
	extern int	errno;
	void		***source;
	void		**array;
	size_t		size;

	source = arr;
	array = *source;
	size = ft_arrsize(array);
	array = ft_arr_resize(array, size + 1, NULL);
	if (array == NULL)
		return (EXIT_FAILURE);
	array[size] = ptr;
	*source = array;
	return (EXIT_SUCCESS);
}

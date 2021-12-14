/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:28 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:57:33 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Counts the number of elements in a list. */
int	ft_lstsize(t_list *lst)
{
	int	retval;

	if (lst == NULL)
		return (0);
	else
	{
		retval = 0;
		while (lst != NULL)
		{
			retval++;
			lst = lst->next;
		}
		return (retval);
	}
}

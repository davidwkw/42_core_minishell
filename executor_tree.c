/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:25:45 by weng              #+#    #+#             */
/*   Updated: 2022/01/14 17:06:37 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Execute 'ptree' by traversing the tree. */
int	ft_execute_ptree(t_ptree *ptree)
{
	int	retval;

	if (ptree == NULL)
	{
		ft_putenv("?=1");
		return (-1);
	}
	else if (ptree->type == CMD)
		return (ft_execute_cmd(ptree->content));
	else if (ptree->type == TOKEN)
	{
		retval = ft_execute_ptree(ptree->left);
		if ((ft_strcmp(ptree->content, "||") == 0 && retval != 0)
			|| (ft_strcmp(ptree->content, "&&") == 0 && retval == 0))
			return (ft_execute_ptree(ptree->right));
		return (retval);
	}
	else
	{
		ft_putendl_fd("ft_execute_ptree: unknown ptree type.", 2);
		return (-1);
	}
}

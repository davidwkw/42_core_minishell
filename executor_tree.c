/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:25:45 by weng              #+#    #+#             */
/*   Updated: 2022/01/19 12:01:59 by weng             ###   ########.fr       */
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

/* Returns the maximum no. of simple commands of any pipeline within 'ptree' */
static int	ft_ptree_max_count(t_ptree *ptree)
{
	int		left_count;
	int		right_count;
	t_cmd	*cmd;

	if (ptree == NULL)
		return (0);
	else if (ptree->type == CMD)
	{
		cmd = ptree->content;
		return (cmd->count);
	}
	else if (ptree->type == TOKEN)
	{
		left_count = ft_ptree_max_count(ptree->left);
		right_count = ft_ptree_max_count(ptree->right);
		if (left_count >= right_count)
			return (left_count);
		else
			return (right_count);
	}
	else
		return (0);
}

/* Deletes heredoc */
void	ft_del_heredoc(t_ptree *ptree)
{
	int		max;
	char	*filename;

	max = ft_ptree_max_count(ptree);
	while (max-- > 0)
	{
		filename = ft_itoa(max);
		filename = ft_strreplace(filename, ft_strjoin(HEREDOC_FILE, filename));
		unlink(filename);
		free(filename);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:56:05 by weng              #+#    #+#             */
/*   Updated: 2022/01/17 16:48:55 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a new simple command */
t_scmd	*ft_scmd_new(void)
{
	t_scmd	*scmd;

	scmd = ft_calloc(sizeof(t_scmd), 1);
	return (scmd);
}

/* Delete a simple command. */
void	ft_scmd_del(void *scmd)
{
	t_scmd	*scmd_;

	scmd_ = scmd;
	ft_lstclear(&(scmd_->argv), free);
	free(scmd);
}

/* 
Add an argument to a simple command, after variable and asterisk
expansions are carried out.
*/
void	ft_scmd_add_arg(t_scmd *scmd, t_list *node)
{
	char	*content;
	char	*file;
	t_list	*files;
	t_list	*ptr;

	content = ft_expand_var(node->content);
	files = ft_expand_star(NULL, content);
	ptr = files;
	while (ptr != NULL)
	{
		file = ft_strtrim(ptr->content, " ");
		if (*file != '\0')
			ft_lstadd_back(&(scmd->argv), ft_lstnew(ft_remove_quote(file)));
		free(file);
		ptr = ptr->next;
	}
	ft_lstclear(&files, free);
	free(content);
	scmd->count++;
}

/* Convert all arguments in a simple command to an array of strings. */
char	**ft_scmd_to_arr(t_scmd *scmd)
{
	return (ft_lst_to_arr(scmd->argv));
}

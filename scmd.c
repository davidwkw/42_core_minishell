/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:56:05 by weng              #+#    #+#             */
/*   Updated: 2022/01/18 09:42:12 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a new in-out struct */
t_inout	*ft_inout_new(t_inout_type type, char *filename)
{
	t_inout	*retval;

	retval = malloc(sizeof(t_inout));
	if (retval == NULL)
	{
		perror("ft_inout_new");
		free(filename);
	}
	else
	{
		retval->type = type;
		retval->filename = filename;
	}
	return (retval);
}

/* Delete an in-out struct */
static void	ft_inout_del(t_inout *inout)
{
	if (inout != NULL)
	{
		free(inout->filename);
		free(inout);
	}
}

/* Create a new simple command */
t_scmd	*ft_scmd_new(void)
{
	t_scmd	*scmd;

	scmd = ft_calloc(sizeof(t_scmd), 1);
	return (scmd);
}

/* Delete a simple command. */
void	ft_scmd_del(t_scmd *scmd)
{
	ft_lstclear(&scmd->argv, free);
	ft_lstclear(&scmd->infile, (void (*)(void *)) ft_inout_del);
	ft_lstclear(&scmd->outfile, (void (*)(void *)) ft_inout_del);
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

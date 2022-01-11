/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:06:01 by kwang             #+#    #+#             */
/*   Updated: 2022/01/11 15:23:45 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Lists all files within directory provided as string.
*/
static t_list	*ft_list_files(char *dir)
{
	DIR			*dir_stream;
	t_dirent	*dir_entry;
	t_list		*filenames;

	filenames = NULL;
	dir_stream = opendir(dir);
	while (1)
	{
		dir_entry = readdir(dir_stream);
		if (dir_entry == NULL)
			break ;
		ft_lstadd_back(&filenames, ft_lstnew(ft_strdup(dir_entry->d_name)));
	}
	return (filenames);
}

/*
Accepts a reference string and a nested array of characters
to match the reference.
Returns 1 if reference string matchs the nested array of characters,
0 if it doesn't.
*/
static int	ft_str_match(char *string, char **match)
{
	int		i;
	char	*addr;

	i = -1;
	while (match[++i])
	{
		addr = ft_strnstr(string, match[i], ft_strlen(string));
		if (addr)
			string = addr + strlen(match[i]);
		else
			return (0);
	}
	return (1);
}

/*
Accepts a string pattern to be searched and a directory string.
Returns a filtered nested array of
filenames that match the search string.
*/
char	**ft_expand_star(char *search, char *dir)
{
	char	**segments;
	char	**filtered_filenames;
	t_list	*filenames;
	t_list	*temp;
	t_list	*filter_buff;

	segments = ft_split(search, '*');
	filenames = ft_list_files(dir);
	filter_buff = NULL;
	temp = filenames;
	while (temp)
	{
		if (ft_str_match(temp->content, segments))
		{
			ft_lstadd_back(&filter_buff, ft_lstnew(temp->content));
			temp->content = NULL;
		}
		temp = temp->next;
	}
	ft_lstclear(&filenames, free);
	filenames = NULL;
	filtered_filenames = ft_lst_to_arr(filter_buff);
	ft_lstclear(&filter_buff, free);
	filter_buff = NULL;
	return (filtered_filenames);
}

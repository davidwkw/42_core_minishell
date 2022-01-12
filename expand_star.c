/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:06:01 by kwang             #+#    #+#             */
/*   Updated: 2022/01/11 15:55:33 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Lists all files within directory provided as string. */
static t_list	*ft_list_files(char *dir)
{
	DIR			*dirp;
	t_dirent	*dirent;
	t_list		*filenames;
	extern int	errno;

	filenames = NULL;
	dirp = ft_opendir(dir);
	if (dirp == NULL)
		return (NULL);
	errno = 0;
	dirent = readdir(dirp);
	while (dirent != NULL)
	{
		ft_lstadd_back(&filenames, ft_lstnew(ft_strdup(dirent->d_name)));
		dirent = readdir(dirp);
	}
	if (errno != 0)
		perror("readdir");
	ft_closedir(dirp);
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
	int		diff;
	char	*addr;

	i = -1;
	while (match[++i])
	{
		addr = string;
		if (strncmp(match[i], "*", 2) == 0)
			continue;
		if (i == 0)
		{
			if (*match[i] == '*')
				addr = ft_strnstr(string, match[i], ft_strlen(string));
			else
				diff = ft_strncmp(string, match[i], ft_strlen(match[i]));
		}
		else
			addr = ft_strnstr(string, match[i], ft_strlen(string));
		if (ft_strncmp(addr, string, ft_strlen(string)) != 0 || diff == 0)
			string = addr + ft_strlen(match[i]);
		else
			return (0);
	}
	return (1);
}

/*
Splits the search string by a given character. If the string begins with a *
it is reappended to the first element of the split list. If the string ends with
a *, the list is expanded and a single element of "*" if added to the end of the
list. Returns the formatted list.
*/
static char	**ft_star_split(char *search, char c)
{
	char	*segments;
	char	*temp;

	segments = ft_split(search, '*');
	if (*search == '*')
	{
		temp = ft_strjoin("*", segments[0]);
		free(segments[0]);
		segments[0] = temp;
	}
	if (search[ft_strlen(search) - 1] == '*')
	{
		ft_memresize(segments, ft_memsize(segments) + 2);
		segments[ft_memsize(segments) - 1] = ft_strdup("*");
	}
	return (segments);
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

	segments = ft_star_split(search, '*');
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:06:01 by kwang             #+#    #+#             */
/*   Updated: 2022/01/12 17:08:10 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Lists all files within directory provided as string. */
static t_list	*ft_list_files(const char *dir, char mode)
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
		if ((ft_strncmp(dirent->d_name, ".", 2) != 0
			|| ft_strncmp(dirent->d_name, "..", 3) != 0)
				|| (mode == 0 && *(dirent->d_name) != '.') || mode == 1)
		ft_lstadd_back(&filenames, ft_lstnew(ft_strdup(dirent->d_name)));
		dirent = readdir(dirp);
	}
	if (errno != 0)
		perror("readdir");
	ft_closedir(dirp);
	return (filenames);
}

/* Returns 1 if 'str' matches the pattern given by 'pattern', or 0 otherwise. */
static int	ft_str_match(char *str, char **pattern)
{
	int		i;
	char	*addr;

	i = -1;
	addr = str;
	while (pattern[++i] != NULL)
	{
		if (ft_strncmp(pattern[i], "*", 2) == 0)
			addr = ft_strchr(addr, '\0');
		else if (i == 0)
		{
			if (*pattern[i] == '*')
				addr = ft_strnstr(addr, pattern[i] + 1, ft_strlen(addr));
			else if (ft_strncmp(addr, pattern[i], ft_strlen(pattern[i])) != 0)
				addr = NULL;
		}
		else
			addr = ft_strnstr(addr, pattern[i], ft_strlen(addr));
		if (addr == NULL)
			return (0);
		addr += ft_strlen(pattern[i] + (*pattern[i] == '*'));
	}
	return (*addr == '\0');
}

/*
Splits the search string by a given character. If the string begins with a *
it is reappended to the first element of the split list. If the string ends with
a *, the list is expanded and a single element of "*" if added to the end of the
list. Returns the formatted list.
*/
static char	**ft_star_split(char *search)
{
	char	**segments;
	char	*temp;

	segments = ft_split(search, '*');
	if (*search == '*')
	{
		temp = ft_strjoin("*", segments[0]);
		free(segments[0]);
		segments[0] = temp;
	}
	if (search[ft_strlen(search) - 1] == '*')
		ft_arradd_back(&segments, ft_strdup("*"));
	return (segments);
}

/*
Returns a linked list containing the failnames that match the 'pattern'
within directory 'dir'. If there is no match at all, return a linked
list containing the 'pattern'.
*/
t_list	*ft_expand_star(const char *dir, char *pattern)
{
	char	**segments;
	t_list	*filenames;
	t_list	*node;

	segments = ft_star_split(pattern);
	filenames = ft_list_files(dir, *pattern == '.');
	node = filenames;
	while (node != NULL)
	{
		if (ft_str_match(node->content, segments) == 0)
			ft_lst_replace_content(node, ft_strdup(""), free);
		node = node->next;
	}
	if (filenames != NULL)
		filenames = ft_lstdelempty(&filenames);
	ft_arrclear(segments, free);
	if (filenames != NULL)
		return (filenames);
	else
		return (ft_lstnew(ft_strdup(pattern)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:06:01 by kwang             #+#    #+#             */
/*   Updated: 2022/01/14 11:34:36 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Lists all content within the directory 'dir'. If 'hidden' is 0, only
return non-hidden files, otherwise only return hidden files.
*/
static t_list	*ft_ls(const char *dir, char hidden)
{
	DIR			*dirp;
	t_dirent	*dirent;
	t_list		*lst;
	char		*name;
	extern int	errno;

	lst = NULL;
	dirp = ft_opendir(dir);
	if (dirp == NULL)
		return (NULL);
	errno = 0;
	dirent = readdir(dirp);
	while (dirent != NULL)
	{
		name = dirent->d_name;
		if ((*name == '.') == (hidden != 0))
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(name)));
		dirent = readdir(dirp);
	}
	if (errno != 0)
		perror("readdir");
	ft_closedir(dirp);
	return (lst);
}

/* Returns 1 if 'str' matches the pattern given by 'pattern', or 0 otherwise. */
static int	ft_str_match(char *str, t_list *pattern)
{
	int		i;
	t_list	*node;
	char	*content;
	char	*addr;

	i = -1;
	addr = str;
	node = pattern;
	while (node != NULL)
	{
		content = node->content;
		if (ft_strncmp(content, "*", 2) == 0)
			addr = ft_strchr(addr, '\0');
		else if (i == 0)
		{
			if (*content == '*')
				addr = ft_strnstr(addr, content + 1, ft_strlen(addr));
			else if (ft_strncmp(addr, content, ft_strlen(content)) != 0)
				addr = NULL;
		}
		else
			addr = ft_strnstr(addr, content, ft_strlen(addr));
		if (addr == NULL)
			return (0);
		addr += ft_strlen(content + (*content == '*'));
		node = node->next;
	}
	return (*addr == '\0');
}

/* Auxiliary recursive function to be called by ft_star_split. */
static t_list	*ft_star_split_aux(char *input, t_list *lst)
{
	char	*end;
	char	*str;

	while (*input == '*')
		input++;
	if (*input == '\0')
		return (lst);
	end = ft_strchr_unquoted(input, '*');
	if (end != NULL)
		str = ft_substr(input, 0, end - input);
	else
		str = ft_strdup(input);
	ft_lstadd_back(&lst, ft_lstnew(str));
	return (ft_star_split_aux(input + ft_strlen(str), lst));
}

/*
Returns a linked list of substring, from splitting the 'input' at each
unquoted '*' character.

If 'input' begins or ends with a '*', the a node containing pointer to
"*" string added to the front or back of the linked list respectively.
*/
static t_list	*ft_star_split(char *input)
{
	t_list	*lst;

	if (*input == '\0')
		return (NULL);
	lst = ft_star_split_aux(input, NULL);
	if (*input == '*')
		ft_lstadd_front(&lst, ft_lstnew(ft_strdup("*")));
	if (input[ft_strlen(input) - 1] == '*')
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup("*")));
	return (lst);
}

/*
Returns a linked list containing the failnames that match the 'pattern'
within directory 'dir'. If there is no match at all, return a linked
list containing the 'pattern'.
*/
t_list	*ft_expand_star(const char *dir, char *pattern)
{
	t_list	*substr;
	t_list	*filenames;
	t_list	*node;

	substr = ft_star_split(pattern);
	filenames = ft_ls(dir, *pattern == '.');
	node = filenames;
	while (node != NULL)
	{
		if (ft_str_match(node->content, substr) == 0)
			ft_lst_replace_content(node, ft_strdup(""), free);
		node = node->next;
	}
	if (filenames != NULL)
		filenames = ft_lstdelempty(&filenames);
	ft_lstclear(&substr, free);
	if (filenames != NULL)
		return (filenames);
	else
		return (ft_lstnew(ft_strdup(pattern)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:06:01 by kwang             #+#    #+#             */
/*   Updated: 2022/01/14 14:22:45 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* Moves the 'str' pointer to the next location matched by 'pattern'. */
static char	*ft_str_match_move(char *str, t_list *pattern)
{
	char	*content;

	if (ft_strncmp(pattern->content, "*", 2) == 0)
		str = ft_strchr(str, '\0');
	else
	{
		content = ft_remove_quote(pattern->content);
		str = ft_strnstr(str, content, ft_strlen(str));
		if (str != NULL)
			str += ft_strlen(content);
		free(content);
	}
	return (str);
}

/* Returns 1 if 'str' matches the pattern given by 'pattern', or 0 otherwise. */
static int	ft_str_match(char *str, t_list *pattern)
{
	char	*content;

	if (ft_strncmp(pattern->content, "*", 2) != 0)
	{
		content = ft_remove_quote(pattern->content);
		if (ft_strncmp(str, content, ft_strlen(content)) == 0)
			str += ft_strlen(content);
		else
			str = NULL;
		free(content);
		pattern = pattern->next;
	}
	else if (ft_strncmp(pattern->content, "*", 2) == 0 && pattern->next != NULL)
		pattern = pattern->next;
	while (str != NULL && *str != '\0' && pattern != NULL)
	{
		str = ft_str_match_move(str, pattern);
		pattern = pattern->next;
	}
	return (str != NULL && *str == '\0' && pattern == NULL);
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

	substr = ft_star_split(pattern);
	filenames = ft_ls(dir, *pattern == '.');
	filenames = ft_lstdelif(
			filenames, (int (*)(void *, void *)) ft_str_match, substr, free);
	ft_lstclear(&substr, free);
	if (filenames != NULL)
		return (filenames);
	else
		return (ft_lstnew(ft_strdup(pattern)));
}

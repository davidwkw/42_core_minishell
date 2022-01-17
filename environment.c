/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:55:59 by weng              #+#    #+#             */
/*   Updated: 2022/01/17 16:28:02 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Get an environment variable from the g_environ global variable. Returns
a pointer to the value, or NULL if there is no match.
*/
char	*ft_getenv(const char *name)
{
	char	**env;
	int		len;

	env = g_environ;
	len = ft_strlen(name);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (&(*env)[len + 1]);
		env++;
	}
	return (NULL);
}

/*
Search through environment variables and replace. Returns non-zero if
replacement is carried out, 0 if not.
*/
static int	ft_replace_environ(char *args)
{
	char	**env;
	char	*equal;
	int		len;

	equal = ft_strchr(args, '=');
	if (equal == NULL)
		len = ft_strlen(args);
	else
		len = equal - args;
	env = g_environ;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, args, len) == 0
			&& ((*env)[len] == '=' || (*env)[len] == '\0'))
		{
			if (equal != NULL)
			{
				free(*env);
				*env = ft_strdup(args);
			}
			return (len);
		}
		env++;
	}
	return (0);
}

/*
Returns 1 'name' is a valid name for an environment variable, else 0.

The name must be "?", or the first character of the name must be one of
'_' or alphabet. The rest of the name must be '_' or alphanumeric.
*/
int	ft_is_valid_varname(const char *name, int include_question)
{
	if (*name == '\0')
		return (0);
	if (ft_strcmp(name, "?") == 0 && include_question == 1)
		return (1);
	if (*name == '_' || ft_isalpha(*name) == 1)
		name++;
	while (*name == '_' || ft_isalnum(*name) == 1)
		name++;
	return (*name == '\0');
}

/*
Change or add an environment variable. Argument 'string' is of the form
name=value. If 'name' does not already exist in the environment, then
'string' is added to the environment. If 'name' does exist, then the
value of 'name' in the environment is change to 'value'.

if 'string' is of the form 'name', then it is added to g_environ but
only considered marked for export.

Returns zero upon success, or non-zero upon failure.
*/
int	ft_putenv(char *string)
{
	char	*equal;
	char	*name;
	int		valid;

	equal = ft_strchr(string, '=');
	if (equal != NULL)
		name = ft_substr(string, 0, equal - string);
	else
		name = ft_strdup(string);
	valid = ft_is_valid_varname(name, 1);
	free(name);
	if (valid == 0)
		return (EXIT_FAILURE);
	if (ft_replace_environ(string) == 0)
		return (ft_arradd_back(&g_environ, ft_strdup(string)));
	else
		return (EXIT_SUCCESS);
}

/*
Wait for the end each child process and put the exit value in the
environment. Returns the exit value of the last simple command.

By default, the return code of a pipeline is the return code of the last
simple command.
*/
int	ft_set_exit_value(t_list *lst)
{
	pid_t	*pid;
	int		wstatus;
	int		value;
	char	*str;

	if (lst == NULL)
		return (ft_atoi(ft_getenv("?")));
	value = 0;
	while (lst != NULL)
	{
		pid = lst->content;
		waitpid(*pid, &wstatus, WUNTRACED);
		if (WIFEXITED(wstatus) == 1)
			value = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus) == 1)
			value = 128 + WTERMSIG(wstatus);
		lst = lst->next;
	}
	str = ft_itoa(value);
	str = ft_strreplace(str, ft_strjoin("?=", str));
	ft_putenv(str);
	free(str);
	return (value);
}

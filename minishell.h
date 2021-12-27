/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:25 by weng              #+#    #+#             */
/*   Updated: 2021/12/27 23:37:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft/libft.h"

// environment variables
extern char	**environ;
extern char	**g_environ;

// char pointer array (string array) functions
size_t	ft_memsize(const char **arr);
char	**ft_memdup(const char **arr);
char	**ft_memresize(char **arr, size_t size);
void	ft_memdel(char **arr);
int		ft_meminsert(char ***dest, char *str);

// string functions
char	*ft_strchr_unquoted(const char *str, int c);
char	*ft_strappend(char *ptr, char *str);
void	ft_strreplace(char **ptr, char *new);

// list related functions that are not included in libft
void	ft_lst_replace_content(t_list *lst, void *content);
void	ft_lstinsert(t_list *lst, t_list *new);
t_list	*ft_lstdelempty(t_list **lst);

// lexer functions
int		ft_istoken(const char *str, char **token);
t_list	*ft_tokenise(char *input);
char	*ft_expand_var(char *str);

// quotation functions
char	*ft_is_properly_quoted(char *str);
char	*ft_remove_quote(char *str);

// environment variable functions
char	*ft_getenv(const char *name);
int		ft_putenv(char *string);

// built-in functions
int		ft_cd(char **args);
int		ft_echo(char **args);
int		ft_env(char **args);
int		ft_exit(char **args);
int		ft_export(char **args);
int		ft_pwd(char **args);
int		ft_unset(char **args);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:25 by weng              #+#    #+#             */
/*   Updated: 2021/12/15 14:34:55 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft/libft.h"

// built-in functions
int	ft_cd(char **args);
int	ft_echo(char **args);
int	ft_env(char **args);
int	ft_exit(char **args);
int	ft_export(char **args);
int	ft_pwd(char **args);
int	ft_unset(char **args);

#endif

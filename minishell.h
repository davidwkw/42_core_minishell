/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:25 by weng              #+#    #+#             */
/*   Updated: 2022/01/07 12:38:56 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include "libft/libft.h"

# define HEREDOC_FILE ".heredoc"
# define HISTORY_FILE ".history"
# define HISTORY_COUNT 35

// data structure for simple command
typedef struct s_scmd
{
	int		count;
	t_list	*argv;
}	t_scmd;

// data structure for command
typedef struct s_cmd
{
	int		count;
	t_list	*scmd_lst;
	char	*infile;
	char	*outfile;
	int		outfile_flag;
}	t_cmd;

// built-in function pointer definition
typedef int	(*t_bif)(char **);

// environment variables
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
char	**ft_lst_to_arr(t_list *lst);

// lexer functions
int		ft_istoken(const char *str, char **token);
t_list	*ft_tokenise(char *input);
void	ft_token_print(t_list *token);
char	*ft_expand_var(char *str);

// simple command functions
t_scmd	*ft_scmd_new(void);
void	ft_scmd_del(void *scmd);
void	ft_scmd_add_arg(t_scmd *scmd, t_list *node);
char	**ft_scmd_to_arr(t_scmd *scmd);

// command functions
t_cmd	*ft_cmd_new(void);
void	ft_cmd_del(t_cmd *cmd);
void	ft_cmd_add_scmd(t_cmd *cmd);
void	ft_cmd_add_arg(t_cmd *cmd, t_list *node);
void	ft_cmd_print(t_cmd *cmd);

// parser functions
t_cmd	*ft_parse(t_list *lst);
int		ft_parse_error(t_cmd *cmd, t_list **lst);
int		ft_hdlr_token(t_cmd *cmd, t_list **lst);

// file descriptor functions
int		ft_dup(int oldfd);
int		ft_pipe_create(int fd[2]);
int		ft_pipe_dup_close(int oldfd, int newfd);
int		ft_open(const char *pathname, int flags, mode_t mode);
int		ft_close(int fd);

// here document, input and output file functions
void	ft_write_heredoc(char *delimiter);
int		open_outfile(t_cmd *cmd);
void	ft_save_restore_fd(void);

// executor functions
pid_t	ft_execute_scmd(t_cmd *cmd, int i);
int		ft_execute_cmd(t_cmd *cmd);

// quotation functions
char	*ft_is_properly_quoted(char *str);
char	*ft_remove_quote(char *str);

// environment variable functions
char	*ft_getenv(const char *name);
int		ft_putenv(char *string);
int		ft_set_exit_value(t_list *lst);

// built-in / external functions
int		ft_cd(char **args);
int		ft_echo(char **args);
int		ft_env(char **args);
int		ft_exit(char **args);
int		ft_export(char **args);
int		ft_pwd(char **args);
int		ft_unset(char **args);
t_bif	ft_builtin(char *name);
void	ft_external(char **args);
void	ft_run(char **arg, int nofork);

// history function
int		is_strdigit(char *string);
int		is_strwhitespace(char *string);
char	*get_line_num(int fd, int num);
int		count_history(void);
void	save_history(char *cmd);
void	ft_init_history(void);
int		ft_history(char **args);

// signal functions
void	ft_init_proc_signals(void);
void	ft_init_rl_signals(void);

#endif

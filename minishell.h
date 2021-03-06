/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:22:25 by weng              #+#    #+#             */
/*   Updated: 2022/01/19 15:49:09 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include "libft/libft.h"

# define HEREDOC_FILE ".heredoc"
# define HISTORY_FILE ".history"
# define HISTORY_COUNT 35

// Bash colour codes
# define GREEN "\033[32m"
# define NORMAL "\033[0m"
# define BOLD "\033[1m"

// typedef for dirent
typedef struct dirent	t_dirent;

typedef enum e_inout_type
{
	SINGLE = 1,
	DOUBLE = 2
}	t_inout_type;

typedef struct s_inout
{
	t_inout_type	type;
	char			*filename;
}	t_inout;

// data structure for simple command
typedef struct s_scmd
{
	int		index;
	int		count;
	t_list	*argv;
	t_list	*infile;
	t_list	*outfile;
}	t_scmd;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

// data structure for command
typedef struct s_cmd
{
	int		valid;
	int		count;
	t_list	*scmd;
}	t_cmd;

typedef enum e_ptree_type
{
	TOKEN,
	CMD
}	t_ptree_type;

// data structure for parse tree
typedef struct s_ptree
{
	void			*content;
	t_ptree_type	type;
	struct s_ptree	*left;
	struct s_ptree	*right;
}	t_ptree;

// built-in function pointer definition
typedef int				(*t_bif)(char **);

// signal handler function pointer definition
typedef void			(*t_shdlr)(int);

// environment variables
extern char				**g_environ;

// array functions
size_t	ft_arrsize(const void *arr);
void	*ft_arrdup(const void *arr, void *(*func)(const void *));
void	*ft_arr_resize(void *arr, size_t size, void (*del)(void *));
void	ft_arrclear(void *arr, void (*del)(void *));
int		ft_arradd_back(void *arr, void *ptr);

// string functions
char	*ft_strchr_unquoted(const char *str, int c);
char	*ft_strreplace(char *ptr, char *new);

// list related functions that are not included in libft
t_list	*ft_lstget(t_list *lst, unsigned int n);
t_list	*ft_lstdelif(t_list *lst, int (*cmp)(void *, void *), void *arg,
			void (*del)(void *));
void	*ft_lst_to_arr(t_list *lst);

// lexer functions
int		ft_istoken(const char *str, char **token, int include_space);
t_list	*ft_tokenise(char *input);
char	*ft_expand_var(char *str);

// simple command functions
t_scmd	*ft_scmd_new(void);
void	ft_scmd_del(t_scmd *scmd);
t_inout	*ft_inout_new(t_inout_type type, char *filename);
void	ft_scmd_add_arg(t_scmd *scmd, t_list *node);

// command functions
t_cmd	*ft_cmd_new(void);
void	ft_cmd_del(t_cmd *cmd);
void	ft_cmd_add_scmd(t_cmd *cmd);
void	ft_cmd_add_arg(t_cmd *cmd, t_list *node);

// parser functions
int		ft_is_end_of_command(t_list *lst);
t_cmd	*ft_parse(t_list **lst);
int		ft_parse_error(t_list *lst);
int		ft_hdlr_token(t_cmd *cmd, t_list **lst);

// ptree functions
t_ptree	*ft_ptree_new(void *content, t_ptree_type type);
void	ft_ptree_delone(t_ptree *node);
void	ft_ptree_clear(t_ptree *node);
int		ft_ptree_height(t_ptree	*node);
void	ft_ptree_apply_postfix(t_ptree *node, void (*func)(t_ptree *));
t_ptree	*ft_treeify(t_list *lst);

// file descriptor functions
int		ft_dup(int oldfd);
int		ft_pipe_create(int fd[2]);
int		ft_pipe_dup_close(int oldfd, int newfd);
int		ft_open(const char *pathname, int flags, mode_t mode);
int		ft_close(int fd);

// here document, input and output file functions
char	*ft_write_heredoc(int index, char *delimiter);
int		ft_open_infile(t_scmd *scmd, int fd);
int		ft_open_outfile(t_scmd *scmd, int fd);
void	ft_save_restore_fd(void);

// executor functions
pid_t	ft_execute_scmd(t_scmd *scmd, int sibling, int islast);
int		ft_execute_cmd(t_cmd *cmd);
int		ft_execute_ptree(t_ptree *ptree);
char	*ft_get_heredoc(int index);
void	ft_del_heredoc(t_ptree *ptree);

// quotation functions
int		ft_is_well_quoted(const char *s);
int		ft_is_well_bracketed(const char *s);
char	*ft_remove_quote(char *str);

// environment variable functions
int		ft_is_valid_varname(const char *name, int include_question);
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
void	ft_run(t_list *argv, int nofork, int status);

// history function
int		ft_isdigit_str(const char *str);
char	*ft_strip_newline(char *str);
int		ft_count_line(const char *pathname);
void	ft_history_save(char *cmd);
int		ft_history(char **args);
char	*ft_get_history_file(void);

// expansion function
t_list	*ft_expand_star(char *dir, char *pattern);

// signal functions
t_shdlr	ft_signal(int signum, t_shdlr handler);
void	ft_new_prompt_line(int exit_code);
void	ft_sighandler_default(void);
void	ft_sighandler_shell(void);

// minishell initialisation related functions
void	ft_init_environment(char **env);
void	ft_init_history(void);

// printing related functions used during development / debugging
void	ft_token_print(t_list *token);
void	ft_scmd_print(t_scmd *scmd);
void	ft_cmd_print(t_cmd *cmd);
void	ft_ptree_print(t_ptree *ptree);

// dir functions
DIR		*ft_opendir(const char *name);
int		ft_closedir(DIR *dirp);
t_list	*ft_ls(const char *dir, char hidden);
char	*ft_pathjoin(const char *dir, const char *path);

#endif

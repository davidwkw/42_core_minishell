# define variables used by implicit rule
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS	= -L. -L$(LIBFT_PATH)
LDLIBS	= -lminishell -lft -lreadline

# define source and object files
SRCS	=	builtin_cd.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_exit.c \
			builtin_export.c \
			builtin_pwd.c \
			builtin_unset.c \
			cmd.c \
			environment.c \
			executor.c \
			expand_var.c \
			filedes.c \
			ft_lst.c \
			init.c \
			io.c \
			lexer.c \
			parser.c \
			parser_handler.c \
			program.c \
			quote.c \
			scmd.c \
			string_array.c \
			string.c \
			history.c \
			history_utils.c \
			signal.c
OBJS	=	$(SRCS:.c=.o)
MAIN	=	minishell.c

# other variables
LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a
LIBRARY		=	libminishell.a
NAME		=	minishell

all: $(NAME)

$(NAME): $(LIBFT) $(LIBRARY) $(MAIN)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(LDFLAGS) $(LDLIBS)

$(LIBRARY): $(OBJS)
	$(AR) -crs $(LIBRARY) $(OBJS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJS)
	$(RM) $(LIBRARY)
	$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: clean fclean all

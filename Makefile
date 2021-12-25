# define variables used by implicit rule
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -L. -L$(LIBFT_PATH)
LDLIBS	= -lminishell -lft -lreadline

# define source and object files
SRCS	=	history.c
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

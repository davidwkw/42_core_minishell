# define variables used by implicit rule
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -L$(LIBFT_PATH)
LDLIBS	= -lft

# define source and object files
SRCS	=	
OBJS	=	$(SRCS:.c=.o)
MAIN	=	minishell.c

# other variables
LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a
NAME		=	minishell

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(LDFLAGS) $(LDLIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: clean

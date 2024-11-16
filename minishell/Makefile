NAME = minishell

LIBFT = ./libft/libft.a

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I./libft -I/usr/readline
LDFLAGS = -lreadline
RM = rm -rf

SRC =	main.c \
	./parsing/validate.c \
	./parsing/tokens.c \
	./parsing/create_list.c \
	./parsing/ft_free.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT) -o $(NAME)


clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C ./libft

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re
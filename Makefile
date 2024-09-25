NAME = minishell

LIBFT = ./include/libft/libft.a

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I./include/libft -I/usr/include/readline
LDFLAGS = -lreadline
RM = rm -rf

SRC = main.c tokens.c validate.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./include/libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT) -o $(NAME)


clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C ./include/libft

fclean: clean
	$(MAKE) fclean -C ./include/libft
	$(RM) $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re
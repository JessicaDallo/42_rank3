# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sheila <sheila@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 11:37:28 by shrodrig          #+#    #+#              #
#    Updated: 2024/11/21 15:37:43 by sheila           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I ./includes
LIBFT_PATH = libft
LIBFT = -L ${LIBFT_PATH} -lft -lreadline

BUILTINS = cd.c echo.c pwd.c export.c unset.c env.c exit.c builtins_utils.c
EXPANSIONS = expansions.c
#REDIRECTS =
SINTAX = sintax.c
ERROR = error.c free.c
VALIDATE = validate.c val_delimiters.c
TOKENS = tokens.c create_tokens.c tokens_utils.c free_tokens.c
#VALGRIND
VALGRIND_FLAGS = --quiet --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --gen-suppressions=all
VALGRIND_SUPP = --suppressions=readline.supp

SRC = $(addprefix builtins/, $(BUILTINS)) $(addprefix expand/, $(EXPANSIONS))  $(addprefix error/, $(ERROR)) $(addprefix validate/, $(VALIDATE)) $(addprefix tokens/, $(TOKENS)) $(addprefix sintax/, $(SINTAX)) main.c
OBJS = ${SRC:.c=.o}

%.o : %.c
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		make -C ${LIBFT_PATH}
		${CC} ${OBJS} ${LIBFT} -o ${NAME}

all: ${NAME}

clean:
		make -C ${LIBFT_PATH} clean
		${RM} ${OBJS}

fclean: clean
		make -C ${LIBFT_PATH} fclean
		${RM} ${NAME}

re: fclean all

valgrind: all
	valgrind $(VALGRIND_FLAGS) $(VALGRIND_SUPP) ./$(NAME)

#leaks: readline.supp
#	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --log-file=output.log ./$(NAME)

#readline.supp:
#	@echo "{" > readline.supp
#	@echo "    leak readline" >> readline.supp
#	@echo "    Memcheck:Leak" >> readline.supp
#	@echo "    ..." >> readline.supp
#	@echo "    fun:readline" >> readline.supp
#	@echo "}" >> readline.supp
#	@echo "{" >> readline.supp
#	@echo "    leak add_history" >> readline.supp
#	@echo "    Memcheck:Leak" >> readline.supp
#	@echo "    ..." >> readline.supp
#	@echo "    fun:add_history" >> readline.supp
#	@echo "}" >> readline.supp

.PHONY: all clean fclean re


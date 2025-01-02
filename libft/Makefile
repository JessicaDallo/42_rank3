# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sheila <sheila@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 09:57:18 by shrodrig          #+#    #+#              #
#    Updated: 2024/11/21 16:41:22 by sheila           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FT_IS = ft_isprint.c ft_isascii.c ft_isalnum.c ft_isdigit.c \
		ft_isalpha.c

FT_TO = ft_tolower.c ft_toupper.c ft_atoi.c ft_itoa.c ft_atoi_base.c \
		flood_fill.c

FT_PUT = ft_putchar.c ft_putstr.c ft_putnbr.c ft_putendl.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

FT_MEM = ft_bzero.c ft_calloc.c ft_memcpy.c ft_memchr.c \
		ft_memcmp.c ft_memset.c ft_memmove.c
		
FT_LST = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

FT_STR = ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c \
		ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
		ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_strnlen.c ft_strncpy.c ft_strndup.c \
		ft_appendchar.c

FT_PRINTF = ft_printf.c ft_print_std.c ft_print_unsigned.c \
		ft_print_hex.c ft_print_pointer.c

FT_GNL = get_next_line.c get_next_line_utils.c

SRC = ${FT_IS} ${FT_TO} ${FT_PUT} ${FT_MEM} ${FT_LST} ${FT_STR} ${FT_PRINTF} ${FT_GNL}

OBJS = ${SRC:.c=.o}
BONUS_OBJS = ${BONUS:.c=.o}
HEADER = libft.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I .

%.o : %.c
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS} ${HEADER}

all: ${NAME}

bonus: ${OBJS} ${BONUS_OBJS}
		ar rcs ${NAME} ${OBJS} ${BONUS_OBJS}

clean:
		${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

.SILENT:

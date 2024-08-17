# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 16:56:12 by pmolzer           #+#    #+#              #
#    Updated: 2024/08/17 21:17:26 by pmolzer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRCS = $(wildcard sources/*.c)

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g
INCLUDES = -I./includes -I./minilibx-linux

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

MLX_PATH = ./minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT} ${MLX_LIB}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${MLX_FLAGS} -o ${NAME}

${LIBFT}:
	@${MAKE} -C ${LIBFT_PATH}

${MLX_LIB}:
	@${MAKE} -C ${MLX_PATH}

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean: 
	@${MAKE} -C ${LIBFT_PATH} clean
	@${MAKE} -C ${MLX_PATH} clean
	@${RM} ${OBJS}

fclean: clean
	@${MAKE} -C ${LIBFT_PATH} fclean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re 
NAME = fractol

SRCS = $(wildcard sources/*.c)

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g
MLXFLAGS = -lmlx -lXext -lX11 -lm
INCLUDES = -I./includes -I./minilibx-linux

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@${MAKE} -C ./libft
	@${MAKE} -C ./minilibx-linux
	@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a ${MLXFLAGS} -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean: 
	@${MAKE} -C ./libft clean
	@${MAKE} -C ./minilibx-linux clean
	@${RM} ${OBJS}

fclean: clean
	@${MAKE} -C ./libft fclean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
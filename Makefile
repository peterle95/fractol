NAME = fractol

SRCS = $(wildcard sources/*.c)

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
MLXFLAGS = -lmlx -lXext -lX11 -lm

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@${MAKE} -C ./libft
	@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a ${MLXFLAGS} -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean: 
	@${MAKE} -C ./libft clean
	@${RM} ${OBJS}

fclean: clean
	@${MAKE} -C ./libft fclean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
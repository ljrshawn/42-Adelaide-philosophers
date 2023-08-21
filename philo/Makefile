CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = *.c

NAME = philo

${NAME}: all

all:
	${CC} ${CFLAGS} ${SRCS} -o ${NAME}

clean:
	${RM} ${NAME}

fclean: clean

re: fclean all

.PHONY: all clean fclean re
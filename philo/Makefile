CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = *.c

NAME = philo

all: ${NAME}

${NAME}:
	@${CC} ${CFLAGS} ${SRCS} -o ${NAME}
	@echo "Successfully create compile file ./${NAME}"

clean:
	@${RM} ${NAME}
	@echo "Successfully delete compile file ./${NAME}"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
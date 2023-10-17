NAME = push_swap

SRC = src/main.cpp  \
		src/PushSwap.cpp

OBJS = ${SRC:.cpp=.o}

CC = c++
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 -g
INCLUDE = -I include

.cpp.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.cpp=.o}

$(NAME): ${OBJS}
		${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
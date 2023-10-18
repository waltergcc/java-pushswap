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

2:	all
		./$(NAME) $(shell shuf -i 1-2000 -n 2)

3:	all
		./$(NAME) $(shell shuf -i 1-2000 -n 3)

10:	all
		./$(NAME) $(shell shuf -i 1-2000 -n 10)

25:	all
		./$(NAME) $(shell shuf -i 1-2000 -n 25)

100:	all
		./$(NAME) $(shell shuf -i 1-2000 -n 100)

500:	all
		./$(NAME) $(shell shuf -i 1-2000 -n 500)

1250:	all
		./$(NAME) $(shell shuf -i 1-2000 -n 1250)

re: fclean all

.PHONY: all clean fclean re 2 3 10 25 100 500 1250
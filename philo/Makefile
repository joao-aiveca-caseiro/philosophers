SRCS		= philosophers.c\
				parsing.c
OBJS		= ${SRCS:.c=.o}
NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all
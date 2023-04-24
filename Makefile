SRCS		= philosophers.c
# BONUS_SRCS	= pipex_bonus.c
OBJS		= ${SRCS:.c=.o}
# BONUS_OBJS	= ${BONUS_SRCS:.c=.o}
NAME		= philo
# NAME_BONUS	= pipex_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME} 

# $(NAME_BONUS):		${BONUS_OBJS}
# 			${CC} ${CFLAGS} ${BONUS_OBJS} -o ${NAME_BONUS} 

# bonus:		$(NAME_BONUS)

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all
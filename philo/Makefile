NAME			=	philo

CC				=	CC
CFLAGS			=	-Wall -Wetra -Werror



SRCS			=
OBJS			=	${SRCS:.c=.o}


HEADER			=	philosophers.h



all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


%.o : %.c	$(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

clean	:
		rm -rf $(OBJS)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean all

.phony	:	all clean fclean re

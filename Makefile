NAME = ./srcs/philo

SRCS = ./srcs/create_philo.c ./srcs/libft.c ./srcs/time.c ./srcs/parsing.c ./srcs/actions.c ./srcs/error_management.c ./srcs/init_philo.c ./srcs/main.c

OBJS = ${SRCS:.c=.o}

INC = ./includes/philosophers.h

CC  = gcc

RM  = rm -f

CFLAGS = -Wall -Wextra -Werror -I ./includes -g

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJS): $(INC)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
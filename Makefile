NAME = ./srcs/philo

SRCS = ./srcs/create_philo.c ./srcs/libft.c

OBJS = ${SRCS:.c=.o}

INC = ./includes/philosophers.h

CC  = gcc

RM  = rm -f

CFLAGS = -Wall -Wextra -Werror -I ./includes

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
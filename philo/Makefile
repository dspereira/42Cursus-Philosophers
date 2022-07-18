NAME		= 	philo

SRCS 		= 	philo.c

OBJS		= 	$(SRCS:.c=.o)

CC			= gcc
#CFLAGS		= -Wall -Wextra -Werror -I.
CFLAGS		= -I.
RM			= rm -f


all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
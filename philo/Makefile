NAME		= 	philo

SRCS			= $(wildcard srcs/*.c) \

OBJS		= 	$(SRCS:.c=.o)

CC			= gcc
CFLAGS		= -g -pthread -Wall -Wextra -Werror -I ./includes
#CFLAGS		= -g -fsanitize=thread -pthread -Wall -Wextra -Werror -I ./includes
RM			= rm -f


all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
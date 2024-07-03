SRCS =  philo.c begin.c utils.c

OBJS = $(SRCS:.c=.o)

NAME = philo

CC = clang

FLAGS = -Wall -Wextra -Werror

INCLUDE = -lpthread


all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
SRCS =  philo_bonus.c start.c utils_bonus.c

OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

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
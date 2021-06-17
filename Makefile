NAME	= philo_one

CC		= clang #-g -Wall -Werror -Wextra
RM		= rm -rf

SRCS_PATH	=	./srcs/
SRCS_NAME	=	main.c				\
				philo.c			\
				handle_input.c		\
				errors.c			\
				tools.c				\
				table_tools.c		\

INC			= -I./includes

SRCS		= $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS		= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(INC) -o $(NAME)

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re

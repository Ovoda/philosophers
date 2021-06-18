NAME	= philo

CC		= clang -g #-Wall -Werror -Wextra
RM		= rm -rf

SRCS_PATH	=	srcs/
OBJS_PATH	=	objs/
SRCS_NAME	=	main.c				\
				new_philo.c			\
				actions.c			\
				routine.c			\
				handle_input.c		\
				errors.c			\
				tools.c				\
				mutex_tools.c		\
				global_tools.c		\

INC			= -I./includes

SRCS		= $(notdir $(shell find $(SRCS_PATH) -type f -name *.c))
OBJS		= $(addprefix $(OBJS_PATH),$(SRCS:.c=.o))

vpath			%.c $(shell find $(SRCS_PATH) -type d)
.SUFFIXES: 		.c .o .h

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
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

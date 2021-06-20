NAME	= philo

CC		= clang
RM		= rm -rf

SRCS_PATH	=	srcs/
OBJS_PATH	=	objs/

INC			= -I./includes

SRCS		= $(notdir $(shell find $(SRCS_PATH) -type f -name *.c))
OBJS		= $(addprefix $(OBJS_PATH),$(SRCS:.c=.o))

vpath			%.c $(shell find $(SRCS_PATH) -type d)
.SUFFIXES: 		.c .o .h

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	$(CC) $(INC) -c $< -o $@

all: init $(NAME)

init:
	@ mkdir -p $(OBJS_PATH)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(INC) -o $(NAME)

clean: 
	$(RM) $(OBJS) $(OBJS_PATH)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re

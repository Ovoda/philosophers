NAME	= philo

CC		= clang -Wall -Wextra -Werror
RM		= rm -rf

LINUX_FLAG = #-lpthread

SRCS_PATH	=	srcs/
OBJS_PATH	=	objs/
INC			= -I./includes
SRCS		= $(notdir $(shell find $(SRCS_PATH) -type f -name *.c))
OBJS		= $(addprefix $(OBJS_PATH),$(SRCS:.c=.o))

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@ mkdir -p $(OBJS_PATH)
	$(CC) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LINUX_FLAG) $(OBJS) $(INC) -o $(NAME)

clean: 
	$(RM) $(OBJS) $(OBJS_PATH)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re

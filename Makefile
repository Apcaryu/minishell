
NAME = minishell

SRC_PATH	= srcs/
OBJ_PATH	= obj/

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -MMD -MP -g3

SRC = main.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
DEPS	= $(addprefix ${OBJ_PATH}, ${SRC:.c=.d})
HEADERS	= -I./headers/
#LIB 	= -L./libft/ -lft

GREEN = "\033[38;5;150m"
CYAN = "\033[38;5;140m"
BOLD = "\033[1m"
NC = "\033[0m"

all : $(NAME) thanks

$(NAME) : $(OBJS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)

clean :
	@rm -rf $(OBJ_PATH)
fclean : clean
	@rm -f $(NAME)

re : fclean all

thanks :

.PHONY : all clean fclean re thanks
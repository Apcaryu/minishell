
NAME = minishell

SRC_PATH	= srcs/
OBJ_PATH	= obj/
SRC_EXEC_PATH = srcs/exec/
SRC_BUILTINS_PATH = srcs/builtins/

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -MMD -MP -g3

SRC = main.c
SRC_EXEC = read_input.c
SRC_BUILTINS = echo.c \
				cd.c \
				pwd.c \
				export.c \
				unset.c

SRCS	  = $(addprefix $(SRC_PATH), $(SRC))
SRCS_EXEC = $(addprefix $(SRC_EXEC_PATH), $(SRC_EXEC))
SRCS_BUILTINS = $(addprefix $(SRC_BUILTINS_PATH), $(SRC_BUILTINS))
OBJ		  = $(SRC:.c=.o)
OBJ_EXEC  = $(SRC_EXEC:.c=.o)
OBJ_BUILTINS = $(SRC_BUILTINS:.c=.o)
OBJS	  = $(addprefix $(OBJ_PATH), $(OBJ) $(OBJ_EXEC) $(OBJ_BUILTINS))
DEPS	  = $(addprefix ${OBJ_PATH}, ${SRC:.c=.d})
HEADERS	  = -I./headers/
LIB 	  = -L./libft_42/ -lft -lreadline

GREEN = "\033[38;5;150m"
CYAN = "\033[38;5;140m"
BOLD = "\033[1m"
NC = "\033[0m"

all : $(NAME) thanks

$(NAME) : $(OBJS)
	make -C ./libft_42/
	$(CC) $(OBJS) $(LIB) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_EXEC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_BUILTINS_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) -o $@ -c $<

clean :
	@rm -rf $(OBJ_PATH)
fclean : clean
	@rm -f $(NAME)

re : fclean all

thanks :

.PHONY : all clean fclean re thanks
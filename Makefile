
NAME = minishell

SRC_PATH	= srcs/
OBJ_PATH	= obj/
SRC_EXEC_PATH = srcs/exec/
SRC_BUILTINS_PATH = srcs/builtins/
SRC_LEXER_PATH = srcs/lexer/
SRC_PARSER_PATH = srcs/parser/

CC				= cc
CFLAGS			= -Wall -Werror -Wextra -MMD -MP -g3

SRC 			= main.c \
					garb_split.c

SRC_EXEC 		= read_input.c \
					# lst_exec.c

SRC_BUILTINS 	= echo.c \
					cd.c \
					pwd.c \
					export.c \
					unset.c \
					env.c \
					exit.c

SRC_LEXER 		= lexer.c \
					lst_lexer.c

SRC_PARSER 		= parser.c \
					lst_parser.c

SRCS	  = $(addprefix $(SRC_PATH), $(SRC))
SRCS_EXEC = $(addprefix $(SRC_EXEC_PATH), $(SRC_EXEC))
SRCS_BUILTINS = $(addprefix $(SRC_BUILTINS_PATH), $(SRC_BUILTINS))
SRCS_LEXER = $(addprefix $(SRC_LEXER_PATH), $(SRC_LEXER))
SRCS_PARSER =$(addprefix $(SRC_PARSER_PATH), $(SRC_PARSER))
OBJ		  = $(SRC:.c=.o)
OBJ_EXEC  = $(SRC_EXEC:.c=.o)
OBJ_BUILTINS = $(SRC_BUILTINS:.c=.o)
OBJ_LEXER = $(SRC_LEXER:.c=.o)
OBJ_PARSER = $(SRC_PARSER:.c=.o)
OBJS	  = $(addprefix $(OBJ_PATH), $(OBJ) $(OBJ_EXEC) $(OBJ_BUILTINS) $(OBJ_LEXER) $(OBJ_PARSER))
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

$(OBJ_PATH)%.o: $(SRC_LEXER_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_PARSER_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) -o $@ -c $<

clean :
	@rm -rf $(OBJ_PATH)
fclean : clean
	@rm -f $(NAME)

re : fclean all

check_leaks:
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --suppressions=.ignore_readline -q ./minishell

thanks :

.PHONY : all clean fclean re thanks
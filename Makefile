NAME = minishell

SRC_PATH	= srcs/
OBJ_PATH	= obj/
SRC_EXEC_PATH = srcs/exec/
SRC_BUILTINS_PATH = srcs/builtins/
SRC_LEXER_PATH = srcs/lexer/
SRC_PARSER_PATH = srcs/parser/
SRC_EXPEND_PATH = srcs/expend/
SRC_SIGNAL_PATH = srcs/signal/
SRC_ERROR_PATH = srcs/error/

CC				= cc
CFLAGS			= -Wall -Werror -Wextra -MMD -MP -g3
CFLAGS			= -MMD -MP -g3 # TODO remove

SRC 			= main.c \
					garb_split.c

SRC_EXEC 		= read_input.c \
					init_exec.c \
					print_exec.c \
					exec_cmd.c \
					close_and_exit.c \
					exec_utils.c \
					builtin_process.c \
					heredoc_process.c \
					env_utils.c \
					open_fds.c \
					pipe_process.c \

SRC_BUILTINS 	= echo.c \
					cd.c \
					pwd.c \
					export.c \
					unset.c \
					env.c \
					exit.c

SRC_LEXER 		= lexer.c \
					lst_lexer.c \
					print_lst.c \
					set_type_special.c \
					get_content.c \
					set_type_char.c \
					lex_utils.c

SRC_PARSER 		= parser.c \
					lst_parser.c \
					printer.c \
					p_utils.c \
					ncommand.c \
					set_elem.c \
					content_fusion.c

SRC_EXPEND = expend.c \
				lex_expend.c \
				utils.c \
				var_info.c \
				set_var_content.c \
				mini_getenv.c

SRC_SIGNAL = use_signal.c

SRC_ERROR = error_token.c

SRCS	  = $(addprefix $(SRC_PATH), $(SRC))
SRCS_EXEC = $(addprefix $(SRC_EXEC_PATH), $(SRC_EXEC))
SRCS_BUILTINS = $(addprefix $(SRC_BUILTINS_PATH), $(SRC_BUILTINS))
SRCS_LEXER = $(addprefix $(SRC_LEXER_PATH), $(SRC_LEXER))
SRCS_PARSER =$(addprefix $(SRC_PARSER_PATH), $(SRC_PARSER))
SRCS_EXPEND = $(addprefix $(SRC_EXPEND_PATH), $(SRC_EXPEND))
SRCS_SIGNAL = $(addprefix $(SRC_SIGNAL_PATH), $(SRC_SIGNAL))
SRCS_ERROR = $(addprefix $(SRC_ERROR_PATH), $(SRC_ERROR)))
OBJ		  = $(SRC:.c=.o)
OBJ_EXEC  = $(SRC_EXEC:.c=.o)
OBJ_BUILTINS = $(SRC_BUILTINS:.c=.o)
OBJ_LEXER = $(SRC_LEXER:.c=.o)
OBJ_PARSER = $(SRC_PARSER:.c=.o)
OBJ_EXPEND = $(SRC_EXPEND:.c=.o)
OBJ_SIGNAL = $(SRC_SIGNAL:.c=.o)
OBJ_ERROR = $(SRC_ERROR:.c=.o)
OBJS	  = $(addprefix $(OBJ_PATH), $(OBJ) $(OBJ_EXEC) $(OBJ_BUILTINS) $(OBJ_LEXER) $(OBJ_PARSER) $(OBJ_EXPEND) $(OBJ_SIGNAL) $(OBJ_ERROR))
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
	@$(CC) $(HEADERS) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_EXEC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_BUILTINS_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_LEXER_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_PARSER_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_EXPEND_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_SIGNAL_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_ERROR_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(HEADERS) $(CFLAGS) -o $@ -c $<

clean :
	@rm -rf $(OBJ_PATH)
fclean : clean
	@rm -f $(NAME)

re : fclean all

check_leaks:
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --suppressions=.ignore_readline -q ./minishell

thanks :

.PHONY : all clean fclean re thanks
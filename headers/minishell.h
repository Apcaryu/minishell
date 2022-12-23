#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "exec.h"
# include "lexer.h"

# ifndef T_DATA
#  define T_DATA

typedef struct s_data
{
	char *input;
	t_list *garb_lst;
	t_token *lexer_lst;
}	t_data;

# endif
#endif
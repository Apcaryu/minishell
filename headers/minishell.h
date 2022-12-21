#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "exec.h"

typedef struct s_data
{
	t_token *lexer_lst;
}	t_data;

#endif
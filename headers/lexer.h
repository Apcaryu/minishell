#ifndef LEXER_H
# define LEXER_H
# include <limits.h>
# include "main.h"
//# include "../libft_42/includes_libft/libft.h"
//# include "../libft_42/includes_libft/garbage.h"
//# include "minishell.h"
//# include "parser.h"
//# include "utils.h"

//typedef enum	e_bool
//{
//	false,
//	true
//}	t_bool;
//
//typedef enum	e_type
//{
//	NONE,
//	INFILE,
//	HEREDOC,
//	OUTFILE,
//	APPEND,
//	PIPE,
//	COMMAND,
//	SINGLE_QUOTE,
//	DOUBLE_QUOTE
//}	t_type;
//
//typedef struct s_token
//{
//	t_type type;
//	char *content;
//	t_bool is_closed;
//	struct s_token	*next;
//}	t_token;

//# ifndef T_DATA
//#  define T_DATA
//
//typedef struct s_data
//{
//	char *input;
//	t_list *garb_lst;
//	t_token *lexer_lst;
//	t_elem_pars	*parser_lst;
//}	t_data;
//# endif

t_token *new_token(t_list **garb_lst);
void	token_add_back(t_token **token_lst, t_token *token);

void lexer(t_data *data);

void p_lex_lst(t_token *lst);

#endif
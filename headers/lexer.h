#ifndef LEXER_H
# define LEXER_H
# include <limits.h>
# include "main.h"

void	print_lst(t_token *token_lst);

t_token	*new_token(t_list **garb_lst);
t_token	*token_last(t_token *token_lst);
void	token_add_back(t_token **token_lst, t_token *token);

void lexer(void);

#endif

#ifndef LEXER_H
# define LEXER_H
# include <limits.h>
# include "main.h"

void	print_lst(t_token *ntoken_lst);

t_token	*new_ntoken(t_list **garb_lst);
t_token	*ntoken_last(t_token *token_lst);
void		ntoken_add_back(t_token **token_lst, t_token *token);

void n_lexer(void);

#endif

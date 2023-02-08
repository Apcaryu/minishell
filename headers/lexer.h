#ifndef LEXER_H
# define LEXER_H
# include <limits.h>
# include "main.h"

void	print_lst(t_token *token_lst);

void	infile_or_heredoc(t_token *token, unsigned int *idx);
void	outfile_or_append(t_token *token, unsigned int *idx);
t_bool	is_pipe(t_token *token, unsigned int *idx);
void	quote(t_token *token, unsigned int *idx);
void	variable_token(t_token *token, unsigned int *idx);

t_bool	is_word(char chr);

char	*set_content(t_token *token, unsigned int *idx);


t_token	*new_token(t_list **garb_lst);
t_token	*token_last(t_token *token_lst);
void	token_add_back(t_token **token_lst, t_token *token);

void lexer(void);

#endif

#ifndef EXPEND_H
# define EXPEND_H
# include "main.h"
# include "lexer.h"

typedef struct	s_varenv
{
	char	*var_name;
	unsigned int	var_size;
	char			*var_content;
	unsigned int	var_content_size;
}	t_varenv;

void	expend(void);

t_token	*lex_expend(char *input, t_token *token_start);

#endif
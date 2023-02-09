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

t_bool	is_type_word(t_type type);
void	init_varenv(t_varenv *varenv);

void	expend(void);

t_token	*lex_expend(char *input);

#endif
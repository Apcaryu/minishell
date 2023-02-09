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

unsigned int	detect_dollar(char *word, unsigned int idx);
unsigned int	variable_size(const char *str, unsigned int idx);
char			*variable_name(char *str, unsigned int idx, unsigned int var_size);
unsigned int	var_content_size(char *var_name);

void	expend(void);

t_token	*lex_expend(char *input);

#endif
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

char	*mini_getenv(t_data *data, char *var_name);

t_bool	is_type_word(t_type type);
void	init_varenv(t_varenv *varenv);

unsigned int	detect_dollar(char *word, unsigned int idx);
unsigned int	variable_size(const char *str, unsigned int idx);
char			*variable_name(char *str, unsigned int idx, unsigned int var_size);
unsigned int	var_content_size(t_data *data, t_varenv varenv);

void	set_var_content(t_token *token);

void	expend(void);

t_token	*lex_expend(char *input);

#endif
#ifndef LEXER_H
# define LEXER_H
# include <limits.h>
# include "../libft_42/includes_libft/libft.h"

typedef enum	e_bool
{
	false,
	true
}	t_bool;

typedef enum	e_type
{
	NONE,
	INPUT,
	HEREDOC,
	OUTPUT,
	APPEND,
	PIPE,
	COMMAND,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_type;

typedef struct s_token
{
	t_type type;
	char *content;
	t_bool is_closed;
	struct s_token	*next;
}	t_token;

void lexer(char *input);

#endif
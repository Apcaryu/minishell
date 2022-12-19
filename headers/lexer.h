#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	int type;
	char *content;
}	t_token;


void lexer(char *input);

#endif
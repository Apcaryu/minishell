#include "../../headers/parser.h"

extern t_data	g_data;

void	parser(void)
{
	t_token *lex_lst;

	lex_lst = g_data.lexer_lst;
	while (lex_lst != NULL)
	{
		printf("type = %d\n", lex_lst->type);
		lex_lst = lex_lst->next;
	}
}

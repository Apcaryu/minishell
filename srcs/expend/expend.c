#include "../headers/expend.h"

extern t_data g_data;

t_bool	is_type_word(t_ntype type)
{
	if (type == WORD || type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
		return (true);
	return (false);
}

void	expend(void)
{
	t_ntoken *token_lst;

	token_lst = g_data.nlexer_lst;
	while (token_lst != NULL)
	{
		if (is_type_word(token_lst->type))
			printf("is_word\n");
		token_lst = token_lst->next;
	}
}
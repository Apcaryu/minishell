#include "../headers/expend.h"

extern t_data g_data;

t_bool	is_type_word(t_ntype type)
{
	if (type == WORD || type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
		return (true);
	return (false);
}

unsigned int	detect_dollar(char *word)
{
	unsigned int	idx;

	while (word[idx] != '\0')
	{
		if (word[idx] == '$')
			return (idx);
		idx++;
	}
	return (UINT_MAX);
}

void	expend(void)
{
	t_ntoken *token_lst;

	token_lst = g_data.nlexer_lst;
	while (token_lst != NULL)
	{
		if (is_type_word(token_lst->type))
			printf("is_word | '$' pos = %u\n", detect_dollar(token_lst->content));
		token_lst = token_lst->next;
	}
}
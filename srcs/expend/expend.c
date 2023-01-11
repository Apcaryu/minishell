#include "../headers/expend.h"

extern t_data g_data;

t_bool	is_type_word(t_ntype type)
{
	if (type == WORD || type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
		return (true);
	return (false);
}

unsigned int	detect_dollar(char *word, unsigned int idx)
{
//	unsigned int	idx;

	while (word[idx] != '\0')
	{
		if (word[idx] == '$')
			return (idx);
		idx++;
	}
	return (UINT_MAX);
}

unsigned int	variable_size(const char *str, unsigned int idx)
{
	unsigned int	len_out;

	len_out = 0;
	idx++;
	while (isalnum(str[idx]) || str[idx] == '_')
	{
		idx++;
		len_out++;
	}
	return (len_out);
}

void	set_var_content(t_ntoken *token)
{
	unsigned int	idx;

	idx = 0;
	while (token->content[idx] != '\0' && idx != UINT_MAX)
	{
		idx = detect_dollar(token->content, idx);
		if (idx == UINT_MAX || token->content[idx] == '\0')
			break ;
		printf("var_size = %u\n", variable_size(token->content, idx));
		printf("content[%u] = %c\n", idx, token->content[idx]);
		idx++;
	}
}

void	expend(void)
{
	t_ntoken *token_lst;

	token_lst = g_data.nlexer_lst;
	while (token_lst != NULL)
	{
		if (is_type_word(token_lst->type))
			set_var_content(token_lst);
		token_lst = token_lst->next;
	}
}
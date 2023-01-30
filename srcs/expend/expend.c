#include "../headers/expend.h"

extern t_data g_data;

t_bool	is_type_word(t_type type)
{
	if (type == COMMAND || type == SINGLE_QUOTE || type == DOUBLE_QUOTE || type == VARIABLE)
		return (true);
	return (false);
}

void	init_varenv(t_varenv *varenv)
{
	varenv->var_name = NULL;
	varenv->var_content = NULL;
	varenv->var_size = 0;
	varenv->var_content_size = 0;
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
	while (ft_isalnum(str[idx]) || str[idx] == '_')
	{
		idx++;
		len_out++;
	}
	return (len_out);
}

char	*variable_name(char *str, unsigned int idx, unsigned int var_size)
{
	char	*var_name;

	var_name = garbage_alloc(&g_data.garb_lst, sizeof(char) * var_size + 2);
	ft_strlcpy(var_name, str + idx, var_size + 2);
	printf("var_name = %s\n", var_name); // TODO remove
	return (var_name);
}

unsigned int	var_content_size(char *var_name)
{
	unsigned int	size;
	char			*tmp;

	tmp = getenv(var_name + 1);
	if (tmp == NULL)
		return (0);
	size = ft_strlen(tmp);
	printf("size = %u\n", size); // TODO remove
	return (size);
}

unsigned int	final_strlen(const char *str, const t_varenv varenv)
{
	unsigned int	str_len;
	unsigned int	len_out;

	printf("---------- calcul total size ----------\n"); // TODO remove
	str_len = ft_strlen(str);
	printf("str_len = %u\n", str_len); // TODO remove
	if (varenv.var_name != NULL) {
		str_len -= varenv.var_size + 1;
		printf("str_len = %u | var_size = %u | result of %u-%u = %u\n", str_len, varenv.var_size, str_len, varenv.var_size, str_len-varenv.var_size); // TODO remove
	}
	len_out = str_len;
	printf("len_out = %u\n", len_out); // TODO remove
	if (varenv.var_content != NULL) {
		len_out += varenv.var_content_size +1;
		printf("len_out = %u | var_content_size = %u | result of %u+%u = %u\n", len_out, varenv.var_content_size, len_out, varenv.var_content_size, len_out+varenv.var_content_size); // TODO remove
	}
	len_out++;
	printf("len_out = %u\n", len_out); // TODO remove
	printf("---------- end of calcul ----------\n"); // TODO remove
	return (len_out);
}

char	*include_var_content(char *str, unsigned int idx, t_varenv varenv)
{
	char			*strout;
	unsigned int	so_idx;

	if (varenv.var_name == NULL)
		return (str);
	so_idx = 0;
	strout = garbage_alloc(&g_data.garb_lst, sizeof(char) * final_strlen(str, varenv)/*(ft_strlen(str) + 1 + varenv.var_content_size + 1)*/);
	printf("total size = %u\n", final_strlen(str, varenv)); // TODO remove
	ft_strlcpy(strout, str, idx + 1);
	printf("1.strout = %s\n", strout); // TODO remove
	so_idx = ft_strlen(strout);
	if (varenv.var_content != NULL) {
		ft_strlcat(strout + so_idx, varenv.var_content, (/*ft_strlen(str) + 1 + */varenv.var_content_size + 1));
	}
	so_idx = ft_strlen(strout);
	printf("2.strout = %s | so_idx = %u\n", strout, so_idx); // TODO remove
	idx += varenv.var_size + 1;
	printf("str + %u = %s | size = %zu\n", idx, str + idx, ft_strlen(str + idx)); // TODO remove
	ft_strlcat(strout + so_idx, str + idx, (ft_strlen(str + idx))+1);
	printf("3.strout = %s\n", strout); // TODO remove
	return (strout);
}

void	remove_quote(char *str)
{
	unsigned int	idx;
	unsigned int	size;

	idx = 0;
	size = ft_strlen(str);
	printf("str = %s\n", str); // TODO remove
	printf("size = %u\n", size); // TODO remove
	while(idx < size - 1/*str[idx + 1] != '\0'*/)
	{
		str[idx] = str[idx + 1];
		idx++;
	}
	if (idx == 0)
		str[idx] = '\0';
	else
		str[idx - 1] = '\0';
	printf("str = %s\n", str); // TODO remove
}

void	set_var_content(t_token *token)
{
	unsigned int	idx;
	t_varenv		var;

	idx = 0;
	while (token->content[idx] != '\0' && idx != UINT_MAX && token->type != SINGLE_QUOTE)
	{
		init_varenv(&var);
		idx = detect_dollar(token->content, idx);
		if (idx == UINT_MAX || token->content[idx] == '\0')
			break ;
		if (ft_isalnum(token->content[idx + 1]) || token->content[idx + 1] == '_')
		{
			var.var_size = variable_size(token->content, idx);
			var.var_name = variable_name(token->content, idx, var.var_size);
			printf("size of %s = %u\n", var.var_name, var.var_size); // TODO remove
			var.var_content_size = var_content_size(var.var_name);
			var.var_content = getenv(var.var_name + 1);
			printf("content of %s = %s\n", var.var_name, var.var_content); // TODO remove
			token->content = include_var_content(token->content, idx, var);
			printf("content[%u] = %c\n", idx, token->content[idx]); // TODO remove
			idx += var.var_content_size;
		}
		else
			idx++;
	}
	if (token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
	{
		remove_quote(token->content);
//		token->type = COMMAND;
	}
	token->type = COMMAND;
	printf("content = %s\n", token->content);
}

t_token	*token_update(t_token *start, t_token *update, t_token *before)
{
	t_token	*output;

	output = start;
	return (output);
}

void	expend(void)
{
	t_token *token_lst;
//	t_token *tmp;
//	t_token *ttmp;

	token_lst = g_data.lexer_lst;
	while (token_lst != NULL)
	{
//		if (token_lst->next != NULL) {
//			if (token_lst->next->type == VARIABLE)
//				ttmp = token_lst;
//		}
		if (is_type_word(token_lst->type))
			set_var_content(token_lst);
//		if (token_lst->type == VARIABLE)
//		{
//			tmp = token_lst->next;
//			printf("tmp = %p | token_content = %s\n", tmp, token_lst->content);
//			token_lst = lex_expend(token_lst->content, ttmp);
//			token_lst->next = tmp;
//			print_lst(g_data.lexer_lst);
//			while (token_lst != tmp && token_lst != NULL && tmp != NULL) {
//				token_lst = token_lst->next;
//				printf("token_lst = %p\n", token_lst);
//				sleep(1);
//			}
//		}
		token_lst = token_lst->next;
	}
	printf("--------------------------------------------\n\n");
	print_lst(g_data.lexer_lst);
	printf("--------------------------------------------\n\n");
}
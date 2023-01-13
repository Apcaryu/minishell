#include "../headers/expend.h"

extern t_data g_data;

t_bool	is_type_word(t_ntype type)
{
	if (type == WORD || type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
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
	while (isalnum(str[idx]) || str[idx] == '_')
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
	printf("var_name = %s\n", var_name);
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
	printf("size = %u\n", size);
	return (size);
}

char	*include_var_content(char *str, unsigned int *idx, t_varenv varenv)
{
	char			*strout;
	unsigned int	so_idx;

	if (varenv.var_name == NULL)
		return (str);
	so_idx = 0;
	strout = garbage_alloc(&g_data.garb_lst, sizeof(char) * (ft_strlen(str) + 1 + varenv.var_content_size + 1));
	printf("total size = %zu\n", (ft_strlen(str) + 1 + varenv.var_content_size + 1));
	ft_strlcpy(strout, str, *idx + 1);
	printf("1.strout = %s\n", strout);
	so_idx += ft_strlen(strout);
	if (varenv.var_content != NULL) {
		ft_strlcat(strout + so_idx, varenv.var_content, (/*ft_strlen(str) + 1 + */varenv.var_content_size + 1));
	}
	printf("2.strout = %s\n", strout);
	*idx += varenv.var_size + 1;
	printf("str + %u = %s\n", *idx, str + *idx);
	ft_strlcat(strout + *idx, str + *idx, (ft_strlen(str + *idx) + 2));
	printf("3.strout = %s\n", strout);
	return (strout);
}

void	remove_quote(char *str)
{
	unsigned int	idx;
	unsigned int	size;

	idx = 0;
	size = ft_strlen(str);
	printf("str = %s\n", str);
	printf("size = %u\n", size);
	while(idx < size - 1/*str[idx + 1] != '\0'*/)
	{
		str[idx] = str[idx + 1];
		idx++;
	}
	if (idx == 0)
		str[idx] = '\0';
	else
		str[idx - 1] = '\0';
	printf("str = %s\n", str);
}

void	set_var_content(t_ntoken *token)
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
		var.var_size = variable_size(token->content, idx);
		var.var_name = variable_name(token->content, idx, var.var_size);
		if (ft_isalnum(var.var_name[1]) || var.var_name[1] == '_')
		{
			var.var_content_size = var_content_size(var.var_name);
			var.var_content = getenv(var.var_name + 1);
			printf("content of %s = %s\n", var.var_name, var.var_content);
			token->content = include_var_content(token->content, &idx, var);
		}
//		var_content_size(variable_name(token->content, idx, variable_size(token->content, idx)));
//		printf("var_size = %u\n", variable_size(token->content, idx));
		printf("content[%u] = %c\n", idx, token->content[idx]);
		idx++;
	}
	if (token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
		remove_quote(token->content);
	printf("content = %s\n", token->content);
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
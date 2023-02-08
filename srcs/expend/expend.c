/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:31:56 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/08 18:31:58 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/expend.h"

extern t_data	g_data;

t_bool	is_type_word(t_type type)
{
	if (type == COMMAND || type == SINGLE_QUOTE || type == DOUBLE_QUOTE || \
	type == VARIABLE)
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
	return (size);
}

unsigned int	final_strlen(const char *str, const t_varenv varenv)
{
	unsigned int	str_len;
	unsigned int	len_out;

	str_len = ft_strlen(str);
	if (varenv.var_name != NULL)
		str_len -= varenv.var_size + 1;
	len_out = str_len;
	if (varenv.var_content != NULL)
		len_out += varenv.var_content_size +1;
	len_out++;
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
		token->type = COMMAND;
	}
	printf("content = %s\n", token->content);
}

void	expend(void)
{
	t_token *token_lst;
	t_token	*start;
	t_token *end;

	token_lst = g_data.lexer_lst;
	if (token_lst->type != VARIABLE)
		start = token_lst;
	else
		start = NULL;
	while (token_lst != NULL)
	{
		if (token_lst->type == HEREDOC)
		{
			token_lst = token_lst->next;
			if (token_lst == NULL)
				return ;
			else
			{
				dprintf(2, "coucou\n");
				if (token_lst->type == C_SPACE)
					token_lst = token_lst->next;
				if (token_lst == NULL)
					return ;
				else
				{
					token_lst = token_lst->next;
					dprintf(2, "\033[33mblop\033[0m\n");
				}
				if (token_lst == NULL)
					return ;
			}
		}
		if (token_lst->type != VARIABLE)
			start = token_lst;
		if (is_type_word(token_lst->type))
			set_var_content(token_lst);
		if (token_lst->type == VARIABLE) {
			if (start == NULL)
				g_data.lexer_lst = lex_expend(token_lst->content);
			else {
				end = token_lst->next;
				start->next = lex_expend(token_lst->content);
				token_lst = start;
				while (token_lst->next != NULL) {
					token_lst = token_lst->next;
				}
				token_lst->next = end;
			}
		}
		token_lst = token_lst->next;
	}
	printf("--------------------------------------------\n\n");
	print_lst(g_data.lexer_lst);
	printf("--------------------------------------------\n\n");
}
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
	strout = garbage_alloc(&g_data.garb_lst, \
	sizeof(char) * final_strlen(str, varenv));
	ft_strlcpy(strout, str, idx + 1);
	so_idx = ft_strlen(strout);
	if (varenv.var_content != NULL)
		ft_strlcat(strout + so_idx, varenv.var_content, \
		(varenv.var_content_size + 1));
	so_idx = ft_strlen(strout);
	idx += varenv.var_size + 1;
	ft_strlcat(strout + so_idx, str + idx, (ft_strlen(str + idx)) + 1);
	return (strout);
}

void	remove_quote(char *str)
{
	unsigned int	idx;
	unsigned int	size;

	idx = 0;
	size = ft_strlen(str);
	while (idx < size - 1)
	{
		str[idx] = str[idx + 1];
		idx++;
	}
	if (idx == 0)
		str[idx] = '\0';
	else
		str[idx - 1] = '\0';
}

t_varenv	set_var(t_token *token, unsigned int idx)
{
	t_varenv	var_out;

	init_varenv(&var_out);
	var_out.var_size = variable_size(token->content, idx);
	var_out.var_name = variable_name(token->content, idx, var_out.var_size);
	var_out.var_content_size = var_content_size(var_out.var_name);
	var_out.var_content = getenv(var_out.var_name + 1);
	return (var_out);
}

void	set_var_content(t_token *token)
{
	unsigned int	idx;
	t_varenv		var;

	idx = 0;
	while (token->content[idx] != '\0' && idx != UINT_MAX && \
	token->type != SINGLE_QUOTE)
	{
		idx = detect_dollar(token->content, idx);
		if (idx == UINT_MAX || token->content[idx] == '\0')
			break ;
		if (ft_isalnum(token->content[idx + 1]) || \
		token->content[idx + 1] == '_')
		{
			var = set_var(token, idx);
			token->content = include_var_content(token->content, idx, var);
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
}

void	special_heredoc(t_token *token_lst)
{
	token_lst = token_lst->next;
	if (token_lst == NULL)
		return ;
	else
	{
		if (token_lst->type == C_SPACE)
			token_lst = token_lst->next;
		if (token_lst == NULL)
			return ;
		else
			token_lst = token_lst->next;
		if (token_lst == NULL)
			return ;
	}
}

void	call_lex(t_data *data, t_token *token_lst, t_token *start, t_token *end)
{
	if (start == NULL)
		data->lexer_lst = lex_expend(token_lst->content);
	else
	{
		end = token_lst->next;
		start->next = lex_expend(token_lst->content);
		token_lst = start;
		while (token_lst->next != NULL)
			token_lst = token_lst->next;
		token_lst->next = end;
	}
}

void	expend(void)
{
	t_token	*token_lst;
	t_token	*start;
	t_token	*end;

	token_lst = g_data.lexer_lst;
	if (token_lst->type != VARIABLE)
		start = token_lst;
	else
		start = NULL;
	while (token_lst != NULL)
	{
		if (token_lst->type == HEREDOC)
			special_heredoc(token_lst);
		if (token_lst->type != VARIABLE)
			start = token_lst;
		if (is_type_word(token_lst->type))
			set_var_content(token_lst);
		if (token_lst->type == VARIABLE)
			call_lex(&g_data, token_lst, start, end);
		token_lst = token_lst->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:38:57 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/09 14:38:58 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/expend.h"

extern t_data	g_data;

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

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

t_token	*special_heredoc(t_token *token_lst)
{
	token_lst = token_lst->next;
	if (token_lst == NULL)
		return (token_lst);
	else
	{
		if (token_lst->type == C_SPACE)
			token_lst = token_lst->next;
		if (token_lst == NULL)
			return (token_lst);
		else
		{
			if (token_lst->type == VARIABLE)
				token_lst->type = COMMAND;
			token_lst = token_lst->next;
		}
		if (token_lst == NULL)
			return (token_lst);
	}
	return (token_lst);
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
		{
			token_lst = special_heredoc(token_lst);
			if (token_lst == NULL)
				return ;
		}
		if (token_lst->type != VARIABLE)
			start = token_lst;
		if (is_type_word(token_lst->type))
			set_var_content(token_lst);
		if (token_lst->type == VARIABLE)
			call_lex(&g_data, token_lst, start, end);
		token_lst = token_lst->next;
	}
}

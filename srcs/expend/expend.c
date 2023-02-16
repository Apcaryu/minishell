/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:31:56 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/16 00:11:14 by apellegr         ###   ########.fr       */
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

t_token	*call_lex(t_token *token_lst, t_token *start, t_token **final_start)
{
	t_token	*end;

	end = token_lst->next;
	if (start == NULL)
	{
		start = lex_expend(token_lst->content);
		*final_start = start;
		token_lst = start;
		while (token_lst->next != NULL)
			token_lst = token_lst->next;
		token_lst->next = end;
	}
	else
	{
		start->next = lex_expend(token_lst->content);
		token_lst = start;
		while (token_lst->next != NULL)
			token_lst = token_lst->next;
		token_lst->next = end;
	}
	return (token_lst);
}

t_token	*init_start(t_token *token_lst, t_token *start, t_token **final_start)
{
	if (token_lst->type != VARIABLE)
	{
		start = token_lst;
		*final_start = token_lst;
	}
	else
		start = NULL;
	return (start);
}

t_token	*expend(void)
{
	t_token	*token_lst;
	t_token	*start;
	t_token	*final_start;

	token_lst = g_data.lexer_lst;
	start = init_start(token_lst, start, &final_start);
	while (token_lst != NULL)
	{
		if (token_lst->type == HEREDOC)
		{
			token_lst = special_heredoc(token_lst);
			if (token_lst == NULL)
				return (final_start);
		}
		if (is_type_word(token_lst->type))
			set_var_content(token_lst);
		if (token_lst->type == VARIABLE)
			token_lst = call_lex(token_lst, start, &final_start);
		start = token_lst;
		token_lst = token_lst->next;
	}
	return (final_start);
}

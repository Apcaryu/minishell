/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:23:27 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/08 14:23:28 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"

extern t_data	g_data;

t_token	*new_token(t_list **garb_lst)
{
	t_token	*new;

	new = garbage_alloc(garb_lst, sizeof(t_token) + 1);
	if (new == NULL)
		return (new);
	new->type = NONE;
	new->content = NULL;
	new->next = NULL;
	return (new);
}

t_token	*token_last(t_token *token_lst)
{
	if (token_lst != NULL)
	{
		while (token_lst->next != NULL)
			token_lst = token_lst->next;
	}
	return (token_lst);
}

void	token_add_back(t_token **token_lst, t_token *token)
{
	t_token	*last_token;

	if (!token_lst || !token)
		return ;
	last_token = token_last(*token_lst);
	if (!last_token)
		*token_lst = token;
	else
		last_token->next = token;
}

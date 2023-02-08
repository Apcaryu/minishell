/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:11:34 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/08 13:11:36 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"

void	print_lst(t_token *token_lst)
{
	if (token_lst == NULL)
		return ;
	while (token_lst != NULL)
	{
		dprintf(2, "token = %p | type = %d | content = %s | next = %p\n", \
		token_lst, token_lst->type, token_lst->content, token_lst->next);
		token_lst = token_lst->next;
	}
}

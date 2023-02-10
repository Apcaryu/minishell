/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:01:30 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/10 11:01:32 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

void	p_token(t_token *token)
{
	if (token == NULL)
		return ;
	printf("token = %p | type = %d | content = %s | next = %p\n", token, \
	token->type, token->content, token->next);
}

void	p_elem(t_elem_pars *elem)
{
	unsigned int	idx;

	idx = 0;
	if (elem == NULL)
		return ;
	printf("elem = %p | type = %d | cmd = %s | ", elem, elem->type, elem->cmd);
	if (elem->args != NULL)
	{
		printf("arg = ");
		while (elem->args[idx] != NULL)
		{
			printf("%s, ", elem->args[idx]);
			idx++;
		}
		printf("| ");
	}
	printf("next = %p\n", elem->next);
}

void	p_lst_elem(t_elem_pars *lst)
{
	if (lst == NULL)
		return ;
	while (lst->next != NULL)
	{
		p_elem(lst);
		lst = lst->next;
	}
	p_elem(lst);
}

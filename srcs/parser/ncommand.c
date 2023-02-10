/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncommand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:23:37 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/10 12:23:38 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

extern t_data	g_data;

unsigned int	nargs_count(t_token *token)
{
	unsigned int	count;
	t_token			*prev;

	count = 0;
	prev = token;
	while (token != NULL)
	{
		if (token->type == COMMAND && !is_in_here_out_append(prev->type))
			count++;
		if (token->type != C_SPACE)
			prev = token;
		token = token->next;
		if (token != NULL)
		{
			if (token->type == PIPE)
				break ;
		}
	}
	return (count);
}

unsigned int	ncommand(t_elem_pars *elem_pars, t_token *token)
{
	unsigned int	nb_move;

	nb_move = 1;
	nb_move = content_fusion_cmd(token, elem_pars, nb_move);
	elem_pars->args = garbage_alloc(&g_data.garb_lst, \
	sizeof(char *) * (nargs_count(token) + 1));
	elem_pars->args[0] = token->content;
	return (nb_move);
}

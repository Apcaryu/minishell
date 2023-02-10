/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:10:30 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/10 11:10:31 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

extern t_data	g_data;

t_bool	is_in_here_out_append(t_type type)
{
	if (type == INFILE || type == HEREDOC || type == OUTFILE || type == APPEND)
		return (true);
	return (false);
}

t_elem_pars	*init_command_elem(void)
{
	t_elem_pars	*command_elem;

	command_elem = garbage_alloc(&g_data.garb_lst, sizeof(t_elem_pars) * 1);
	command_elem->type = NONE;
	return (command_elem);
}

t_token	*move_tlst(t_token *lex_lst, unsigned int nb_move)
{
	while (nb_move != 0)
	{
		if (lex_lst->next == NULL)
		{
			lex_lst = NULL;
			break ;
		}
		lex_lst = lex_lst->next;
		nb_move--;
	}
	return (lex_lst);
}

t_token	*space_jump(t_token *lex_lst)
{
	if (lex_lst->next == NULL)
		return (lex_lst);
	if (lex_lst->type == C_SPACE)
		lex_lst = lex_lst->next;
	return (lex_lst);
}

void	add_elem(t_data *data, t_elem_pars *elem)
{
	if (elem->type != ARGS)
		elem_pars_add_back(&data->parser_lst, elem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:31:37 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/09 16:31:37 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"
#include "../../headers/lexer.h"

extern t_data	g_data;

t_elem_pars	*create_elem(t_elem_pars *elem)
{
	if (elem == NULL)
		return (new_elem_pars(&g_data.garb_lst));
	else
	{
		if (elem->type != ARGS)
			elem = new_elem_pars(&g_data.garb_lst);
	}
	return (elem);
}

t_elem_pars	*set_cmd(t_elem_pars *elem, t_elem_pars *cmd_elem)
{
	if (elem->type == COMMAND)
		cmd_elem = elem;
	else if (elem->type == PIPE)
		cmd_elem = init_command_elem();
	return (cmd_elem);
}

t_elem_pars	*combine_cmd_add(t_data *data, t_elem_pars *elem, \
								t_elem_pars *cmd_elem)
{
	cmd_elem = set_cmd(elem, cmd_elem);
	add_elem(data, elem);
	return (cmd_elem);
}

t_token	*init_parser(t_data *data, t_token *lex_lst, t_elem_pars **elem)
{
	lex_lst = data->lexer_lst;
	*elem = NULL;
	return (lex_lst);
}

void	parser(void)
{
	t_token			*lex_lst;
	t_elem_pars		*elem;
	t_elem_pars		*cmd_elem;
	unsigned int	idx;

	idx = 1;
	cmd_elem = init_command_elem();
	lex_lst = init_parser(&g_data, lex_lst, &elem);
	while (lex_lst != NULL)
	{
		elem = create_elem(elem);
		lex_lst = move_tlst(lex_lst, set_elem(elem, lex_lst, cmd_elem, &idx));
		cmd_elem = combine_cmd_add(&g_data, elem, cmd_elem);
		if (lex_lst == NULL)
			break ;
		lex_lst = space_jump(lex_lst);
		if (lex_lst->next == NULL)
		{
			elem = create_elem(elem);
			set_elem(elem, lex_lst, cmd_elem, &idx);
			add_elem(&g_data, elem);
			break ;
		}
	}
	p_lst_elem(g_data.parser_lst);
}

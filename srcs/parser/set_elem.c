/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:29:06 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/10 12:29:07 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

extern t_data	g_data;

unsigned int	in_her_out_app(t_elem_pars *elem, t_token *token)
{
	unsigned int	nb_move;

	nb_move = 0;
	elem->type = token->type;
	nb_move++;
	if (token->next != NULL)
		token = token->next;
	else
		return (nb_move);
	if (token->type == C_SPACE)
	{
		nb_move++;
		if (token->next == NULL)
			return (nb_move);
		else
			token = token->next;
	}
	if (token->type == COMMAND)
	{
		nb_move++;
		elem->args = garbage_alloc(&g_data.garb_lst, sizeof(char *) * 2);
		elem->args[0] = token->content;
		elem->args[1] = NULL;
	}
	return (nb_move);
}

unsigned int	pipe_operator(t_elem_pars *elem, t_token *token)
{
	elem->type = token->type;
	return (1);
}

unsigned int	set_elem(t_elem_pars *elem_pars, t_token *token, \
t_elem_pars *cmd, unsigned int *idx)
{
	unsigned int	nb_move;

	nb_move = 1;
	if (is_in_here_out_append(token->type))
		nb_move = in_her_out_app(elem_pars, token);
	else if (token->type == PIPE)
	{
		nb_move = pipe_operator(elem_pars, token);
		*idx = 1;
	}
	else if (token->type == COMMAND)
	{
		if (cmd->type == NONE)
		{
			elem_pars->type = COMMAND;
			nb_move = ncommand(elem_pars, token);
		}
		else
		{
			elem_pars->type = ARGS;
			cmd->args[*idx] = fusion_arg(token, cmd->args[*idx], &nb_move);
			*idx += 1;
		}
	}
	return (nb_move);
}

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

t_bool	is_in_here_out_append(t_type type)
{
	if (type == INFILE || type == HEREDOC || type == OUTFILE || type == APPEND)
		return (true);
	return (false);
}

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
	elem_pars->cmd = token->content;
	elem_pars->args = garbage_alloc(&g_data.garb_lst, \
	sizeof(char *) * (nargs_count(token) + 1));
	elem_pars->args[0] = token->content;
	return (nb_move);
}

unsigned int	set_elem(t_elem_pars *elem_pars, t_token *token, \
t_elem_pars *command_elem, unsigned int *idx)
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
		if (command_elem->type == NONE)
		{
			elem_pars->type = COMMAND;
			nb_move = ncommand(elem_pars, token);
		}
		else
		{
			elem_pars->type = ARGS;
			command_elem->args[*idx] = token->content;
			*idx += 1;
		}
	}
	return (nb_move);
}

t_elem_pars	*create_elem(t_elem_pars *elem)
{
	if (elem == NULL)
		return (elem);
	else
	{
		if (elem->type != ARGS)
			elem = new_elem_pars(&g_data.garb_lst);
	}
	return (elem);
}

void	add_elem(t_data *data, t_elem_pars *elem)
{
	if (elem->type != ARGS)
		elem_pars_add_back(&data->parser_lst, elem);
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

t_elem_pars	*set_cmd(t_elem_pars *elem, t_elem_pars *cmd_elem)
{
	if (elem->type == COMMAND)
		cmd_elem = elem;
	else if (elem->type == PIPE)
		cmd_elem = init_command_elem();
	return (cmd_elem);
}

t_token	*space_jump(t_token *lex_lst)
{
	if (lex_lst->next == NULL)
		return (lex_lst);
	if (lex_lst->type == C_SPACE)
		lex_lst = lex_lst->next;
	return (lex_lst);
}

void	parser(void)
{
	t_token			*lex_lst;
	t_elem_pars		*elem;
	t_elem_pars		*cmd_elem;
	unsigned int	idx;

	idx = 1;
	lex_lst = g_data.lexer_lst;
	cmd_elem = init_command_elem();
	while (lex_lst != NULL)
	{
		elem = create_elem(elem);
		lex_lst = move_tlst(lex_lst, set_elem(elem, lex_lst, cmd_elem, &idx));
		cmd_elem = set_cmd(elem, cmd_elem);
		add_elem(&g_data, elem);
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
}

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

t_bool	is_redirect(t_type type)
{
	if (type == INFILE || type == HEREDOC || type == OUTFILE || \
	type == APPEND || type == PIPE)
		return (true);
	return (false);
}

unsigned int	nb_arg(t_token *token)
{
	unsigned int	nb_arg;

	nb_arg = 0;
	while (token != NULL)
	{
		if (token->type == C_SPACE)
		{
			if (token->next == NULL)
				return (nb_arg);
			else
				token = token->next;
		}
		if (is_redirect(token->type))
			return (nb_arg);
		if (token->type == COMMAND)
			nb_arg++;
		if (token == NULL)
			return (nb_arg);
		else
			token = token->next;
	}
	return (nb_arg);
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

	nb_move = 0;
	elem_pars->cmd = token->content;
	elem_pars->args = garbage_alloc(&g_data.garb_lst, sizeof(char *) * (nargs_count(token) + 1));
	elem_pars->args[0] = token->content;
//	dprintf(2, "nb_args = %u\n", nargs_count(token));
	return (nb_move);
}

void	get_args(t_elem_pars *command, t_token *token)
{
	static int	idx = 1;

	command->args[idx] = token->content;
	idx++;
}

unsigned int	set_elem_pars(t_elem_pars *elem_pars, t_token *token, t_elem_pars *command_elem, unsigned int *idx)
{
	unsigned int	nb_move;

	nb_move = 0;
	if (token->type == INFILE || token->type == HEREDOC || \
		token->type == OUTFILE || token->type == APPEND)
		nb_move = in_her_out_app(elem_pars, token);
	else if (token->type == PIPE) {
		nb_move = pipe_operator(elem_pars, token);
		*idx = 1;
	}
	else if (token->type == COMMAND) {
//		nb_move = command(elem_pars, token);
		if (command_elem->type == NONE) {
			elem_pars->type = COMMAND;
			nb_move = ncommand(elem_pars, token);
		}
		else {
			elem_pars->type = ARGS;
			dprintf(2, "idx = %u\n", *idx);
			command_elem->args[*idx] = token->content;
			*idx += 1;
//			get_args(command_elem, token);
			dprintf(2, "/033[33margs[%u] = %s/033[0m\n", *idx, command_elem->args[*idx]);
		}
	}
	// ----- ONLY FOR TEST -----//
	if (nb_move == 0)
		nb_move++;
	// ----- END -----//
	return (nb_move);
}

void	parser(void)
{
	t_token	*lex_lst;
	t_elem_pars		*elem;
	unsigned int	nb_move;
	t_bool			is_last;
	t_elem_pars		*command_elem;
	unsigned int	idx;

	idx = 1;
	lex_lst = g_data.lexer_lst;
	command_elem = garbage_alloc(&g_data.garb_lst, sizeof(t_elem_pars) * 1);
	command_elem->type = NONE;
	elem = new_elem_pars(&g_data.garb_lst);
	while (lex_lst != NULL)
	{
		is_last = false;
		nb_move = 0;
		if (lex_lst->next == NULL)
			is_last = true;
//		printf("lex_lst = %p\n", lex_lst);
		if (elem != NULL) {
			if (elem->type != ARGS)
				elem = new_elem_pars(&g_data.garb_lst);
		}
		nb_move = set_elem_pars(elem, lex_lst, command_elem, &idx);
		if (elem->type == COMMAND)
			command_elem = elem;
		else if (elem->type == PIPE) {
			command_elem = garbage_alloc(&g_data.garb_lst, sizeof(t_elem_pars) * 1);
			command_elem->type = NONE;
		}
		p_elem(elem);
//		printf("elem = %p | type = %d | cmd = %s | next = %p\n", elem, elem->type, elem->cmd, elem->next);
		if (elem->type != ARGS)
			elem_pars_add_back(&g_data.parser_lst, elem);
		while (nb_move != 0)
		{
			if (lex_lst->next == NULL)
			{
				lex_lst = NULL;
				break;
			}
			lex_lst = lex_lst->next;
//			printf("lex_lst = %p | next = %p\n", lex_lst, lex_lst->next);
			nb_move--;
//			printf("nb_move = %u\n", nb_move);
		}
		if (lex_lst == NULL)
			break ;
		if (lex_lst->type == C_SPACE && lex_lst->next != NULL)
			lex_lst = lex_lst->next;
		if (lex_lst->next == NULL)
		{
			if (is_last == false)
			{
				if (elem->type != ARGS)
					elem = new_elem_pars(&g_data.garb_lst);
				set_elem_pars(elem, lex_lst, command_elem, &idx);
				p_elem(elem);
				if (elem->type != ARGS)
					elem_pars_add_back(&g_data.parser_lst, elem);
			}
			break ;
		}
//		elem = NULL;
//		sleep(1);
	}
	p_lst_elem(g_data.parser_lst);
}

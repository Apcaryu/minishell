#include "../../headers/parser.h"

extern t_data	g_data;

// ---------- ONLY FOR TEST ---------- //
// TODO remove
void	p_token(t_token *token)
{
	if (token == NULL)
		return ;
	printf("token = %p | type = %d | content = %s | next = %p\n", token, token->type, token->content, token->next);
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

void p_lst_elem(t_elem_pars *lst)
{
	if (lst == NULL) {
		return;
	}
	while (lst->next != NULL)
	{
		p_elem(lst);
		lst = lst->next;
	}
	p_elem(lst);
}
// ---------- END ---------- //

unsigned int	in_her_out_app(t_elem_pars *elem, t_token *token)
{
	unsigned int	nb_move;

	nb_move = 0;
	elem->type = token->type;
	nb_move++;
	if (token->next != NULL)
		token = token->next;
	else
		return(nb_move);
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
	return(nb_move);
}

unsigned int	pipe_operator(t_elem_pars *elem, t_token *token)
{
	elem->type = token->type;
	return (1);
}

unsigned int	nb_arg(t_token *token)
{
	unsigned int	nb_arg;

	nb_arg = 0;
	while (token->next != NULL)
	{
		if (token->type == C_SPACE)
		{
			if (token->next == NULL)
				return (nb_arg);
			else
				token = token->next;
		}
		if (token->type == INFILE || token->type == HEREDOC || \
		token->type == OUTFILE || token->type == APPEND || token->type == PIPE)
			return (nb_arg);
		if (token->type == COMMAND)
			nb_arg++;
		if (token->next == NULL)
			return (nb_arg);
		else
			token = token->next;
	}
	if (token->type == INFILE || token->type == HEREDOC || token->type == C_SPACE || \
		token->type == OUTFILE || token->type == APPEND || token->type == PIPE)
		return (nb_arg);
	else
		nb_arg++;
	return (nb_arg);
}

unsigned int	command(t_elem_pars *elem, t_token *token)
{
	unsigned int	nb_move;
	unsigned int	args;
	unsigned int	idx;
	char			*tmp_cmd;

	nb_move = 0;
	elem->type = token->type;
	elem->cmd = token->content;
	nb_move++;
	p_token(token);
	if (token->next != NULL)
		token = token->next;
	else
		return (nb_move);
	p_token(token);
	while (token->type == COMMAND)
	{
		nb_move++;
		tmp_cmd = garbage_alloc(&g_data.garb_lst, ft_strlen(elem->cmd) +
				ft_strlen(token->content) + 1);
		ft_strlcpy(tmp_cmd, elem->cmd, ft_strlen(elem->cmd) + 1);
		ft_strlcat(tmp_cmd, token->content, ft_strlen(token->content) +
				ft_strlen(tmp_cmd) + 1);
		elem->cmd = tmp_cmd;
		if (token->next != NULL)
			token = token->next;
		else
			return (nb_move);
	}
	if (token->type == C_SPACE)
	{
		nb_move++;
		if (token->next == NULL)
			return (nb_move);
		else
			token = token->next;
	}
	p_token(token);
	if (token->type == INFILE || token->type == HEREDOC || \
		token->type == OUTFILE || token->type == APPEND || token->type == PIPE)
		return (nb_move);
	args = nb_arg(token);
//	printf("nb_args = %u\n", args); // TODO remove
	elem->args = garbage_alloc(&g_data.garb_lst, sizeof(char *) * args + 1);
	idx = 0;
	while (0 < args)
	{
		if (token->type == C_SPACE)
		{
			nb_move++;
			if (token->next == NULL)
				return (nb_move);
			else
				token = token->next;
		}
		else if (token->type != INFILE && token->type != HEREDOC && \
		token->type != OUTFILE && token->type != APPEND && token->type != PIPE)
		{
			elem->args[idx] = token->content;
			if (token->next == NULL)
				break ;
			else
				token = token->next;
			args--;
			idx++;
			nb_move++;
		}
//		if (token->next == NULL) {
//			return (nb_move);
//		}
//		else {
//			token = token->next;
//		}
	}
	if (token->next == NULL)
	{
		if (token->type == INFILE || token->type == HEREDOC || token->type == C_SPACE || \
		token->type == OUTFILE || token->type == APPEND || token->type == PIPE)
			return (nb_move);
		elem->args[idx] = token->content;
		nb_move++;
	}
	return (nb_move);
}

unsigned int	set_elem_pars(t_elem_pars *elem_pars, t_token *token)
{
	unsigned int	nb_move;

	nb_move = 0;
	if (token->type == INFILE || token->type == HEREDOC || \
		token->type == OUTFILE || token->type == APPEND)
		nb_move = in_her_out_app(elem_pars, token);
	else if (token->type == PIPE)
		nb_move = pipe_operator(elem_pars, token);
	else if (token->type == COMMAND)
		nb_move = command(elem_pars, token);
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

	lex_lst = g_data.nlexer_lst;
	while (lex_lst != NULL)
	{
		is_last = false;
		nb_move = 0;
		if (lex_lst->next == NULL)
			is_last = true;
//		printf("lex_lst = %p\n", lex_lst);
		elem = new_elem_pars(&g_data.garb_lst);
		nb_move = set_elem_pars(elem, lex_lst);
		p_elem(elem);
//		printf("elem = %p | type = %d | cmd = %s | next = %p\n", elem, elem->type, elem->cmd, elem->next);
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
				elem = new_elem_pars(&g_data.garb_lst);
				set_elem_pars(elem, lex_lst);
				p_elem(elem);
				elem_pars_add_back(&g_data.parser_lst, elem);
			}
			break ;
		}
		elem = NULL;
//		sleep(1);
	}
	p_lst_elem(g_data.parser_lst);
}
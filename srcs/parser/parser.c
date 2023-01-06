#include "../../headers/parser.h"

extern t_data	g_data;

/*
char	*set_cmd(t_elem_pars *elem_pars, t_token token, unsigned int *idx)
{
//	unsigned int	idx;
	char			*cmd;

//	idx = 0;
//	printf("content = %s\n", token.content);
	while (token.content[*idx] != ' ' && token.content[*idx] !='\0')
		*idx += 1;
	cmd = garbage_alloc(&g_data.garb_lst, sizeof(char) * (*idx + 1));
//	printf("idx = %u\n", idx);
	ft_strlcpy(cmd, token.content, *idx + 1);
//	printf("cmd = %s\n", cmd);
	return (cmd);
}

void	set_elem_pars(t_elem_pars *elem_pars, t_token token)
{
	unsigned int	idx;
	char			*content;

	idx = 0;
	if (token.content == NULL)
		content = NULL;
	else
		content = token.content;
	elem_pars->type = token.type;
	if (token.type == PIPE)
		return ;
	if (token.type == COMMAND || token.type == HEREDOC)
		elem_pars->cmd = set_cmd(elem_pars, token, &idx);
//	printf("idx = %u | content = %s\n", idx, content + idx);
	if (token.content[idx] != '\0' && token.content != NULL)
		elem_pars->args = garb_split(content + idx, ' ', g_data.garb_lst);
}

void	p_args(char **args)
{
	unsigned int	idx = 0;

	if (args == NULL)
		return ;
	idx = 0;
	printf("args:\n");
	while (args[idx])
	{
		printf("%s\n", args[idx]);
		idx++;
	}
}

void	parser(void)
{
	t_token *lex_lst;
	t_elem_pars *elem_pars;

	lex_lst = g_data.lexer_lst;
	while (lex_lst != NULL)
	{
//		printf("type = %d\n", lex_lst->type); // TODO remove
		elem_pars = new_elem_pars(&g_data.garb_lst);
		set_elem_pars(elem_pars, *lex_lst);
		printf("elem = %p | type = %d | cmd = %s\n", elem_pars, elem_pars->type, elem_pars->cmd);
//		p_args(elem_pars->args);
		elem_pars_add_back(&g_data.parser_lst, elem_pars);
//		printf("last = %p\n", elem_pars_last(g_data.parser_lst)); // TODO remove
		lex_lst = lex_lst->next;
	}
}
*/

// ---------- ONLY FOR TEST ---------- //
// TODO remove
void	p_elem(t_nelem *elem)
{
	unsigned int	idx;

	idx = 0;
	if (elem == NULL)
		return ;
	printf("elem = %p | type = %d | cmd = %s | ", elem, elem->type, elem->cmd);
	if (elem->args != NULL)
	{
		while (elem->args[idx] != NULL)
		{
			printf("arg = %s | ", elem->args[idx]);
			idx++;
		}
	}
	printf("next = %p\n", elem->next);
}

void p_lst_elem(t_nelem *lst)
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

unsigned int	in_her_out_app(t_nelem *elem, t_ntoken *token)
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
	if (token->type == WORD)
	{
		nb_move++;
		elem->args = garbage_alloc(&g_data.garb_lst, sizeof(char *) * 2);
		elem->args[0] = token->content;
		elem->args[1] = NULL;
	}
	return(nb_move);
}

unsigned int	set_elem_pars(t_nelem *elem_pars, t_ntoken *token)
{
	unsigned int	nb_move;

	nb_move = 0;
	if (token->type == INFILE || token->type == HEREDOC || \
		token->type == OUTFILE || token->type == APPEND)
		nb_move = in_her_out_app(elem_pars, token);
	// ----- ONLY FOR TEST -----//
	if (nb_move == 0)
		nb_move++;
	// ----- END -----//
	return (nb_move);
}

void	parser(void)
{
	t_ntoken	*lex_lst;
	t_nelem		*elem;
	unsigned int	nb_move;

	lex_lst = g_data.nlexer_lst;
	while (lex_lst != NULL)
	{
		nb_move = 0;
//		printf("lex_lst = %p\n", lex_lst);
		elem = new_elem_pars(&g_data.garb_lst);
		nb_move = set_elem_pars(elem, lex_lst);
		p_elem(elem);
//		printf("elem = %p | type = %d | cmd = %s | next = %p\n", elem, elem->type, elem->cmd, elem->next);
		elem_pars_add_back(&g_data.parser_lst, elem);
		while (nb_move != 0)
		{
			if (lex_lst->next == NULL)
				break ;
			lex_lst = lex_lst->next;
//			printf("lex_lst = %p | next = %p\n", lex_lst, lex_lst->next);
			nb_move--;
//			printf("nb_move = %u\n", nb_move);
		}
		if (lex_lst->next == NULL)
			break ;
//		sleep(1);
	}
	p_lst_elem(g_data.parser_lst);
}
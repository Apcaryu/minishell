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

void	set_elem_pars(t_nelem *elem_pars, t_ntoken token)
{
	return ;
}

void	parser(void)
{
	t_ntoken	*lex_lst;
	t_nelem		*elem;

	lex_lst = g_data.nlexer_lst;
	while (lex_lst != NULL)
	{
		new_elem_pars(&g_data.garb_lst);
		set_elem_pars(elem, *lex_lst);
		elem_pars_add_back(&g_data.parser_lst, elem);
		lex_lst = lex_lst->next;
	}
}
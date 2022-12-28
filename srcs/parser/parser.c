#include "../../headers/parser.h"

extern t_data	g_data;

char	*set_cmd(t_elem_pars *elem_pars, t_token token)
{
	unsigned int	idx;
	char			*cmd;

	idx = 0;
	printf("content = %s\n", token.content);
	while (token.content[idx] != ' ' && token.content[idx] !='\0')
		idx++;
	cmd = garbage_alloc(&g_data.garb_lst, sizeof(char) * idx + 1);
	printf("idx = %u\n", idx);
	ft_strlcpy(cmd, token.content, idx + 1);
	printf("cmd = %s\n", cmd);
	return (cmd);
}

void	set_elem_pars(t_elem_pars *elem_pars, t_token token)
{
	elem_pars->type = token.type;
	if (token.type == COMMAND)
		elem_pars->cmd = set_cmd(elem_pars, token);
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
		elem_pars_add_back(&g_data.parser_lst, elem_pars);
//		printf("last = %p\n", elem_pars_last(g_data.parser_lst)); // TODO remove
		lex_lst = lex_lst->next;
	}
}

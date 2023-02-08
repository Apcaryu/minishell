#include "../../headers/lexer.h"

extern t_data	g_data;

t_bool	is_word(char chr)
{
	if (chr != '<' && chr != '>' && chr != '|' && chr != ' ' && chr != '\'' \
	&& chr != '\"')
		return (true);
	return (false);
}

t_bool	is_quote(t_token *token, unsigned int *idx)
{
	if (g_data.input[*idx] == '\'' || g_data.input[*idx] == '\"')
		return (true);
	return (false);
}

void	set_ntoken(t_token *token, unsigned int *idx)
{
	printf("input[%u] = %c\n", *idx, g_data.input[*idx]);
	if (g_data.input[*idx] == '<')
	{
		infile_or_heredoc(token, idx);
	}
	else if (g_data.input[*idx] == '>')
		outfile_or_append(token, idx);
	else if (is_pipe(token, idx))
		quote(token, idx);
	else if (is_quote(token, idx))
		return ;
	else if (g_data.input[*idx] == ' ')
		space(token, idx);
	else if (g_data.input[*idx] == '$')
		variable_token(token, idx);
	else if (is_word(g_data.input[*idx]))
		word(token, idx);
}

void	lexer(void)
{
	t_token			*token;
	unsigned int	idx;

	idx = 0;
	while (idx < ft_strlen(g_data.input))
	{
		token = new_token(&g_data.garb_lst);
		set_ntoken(token, &idx);
		token_add_back(&g_data.lexer_lst, token);
	}
	print_lst(g_data.lexer_lst);
}

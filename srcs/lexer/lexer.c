#include "../../headers/lexer.h"

extern t_data g_data;

void	print_lst(t_token *ntoken_lst)
{
	if (ntoken_lst == NULL)
		return ;
	while (ntoken_lst->next != NULL)
	{
		printf("case = %p | type = %d | content = %s | next = %p\n", ntoken_lst, ntoken_lst->type, ntoken_lst->content, ntoken_lst->next);
		ntoken_lst = ntoken_lst->next;
	}
	printf("case = %p | type = %d | content = %s | next = %p\n", ntoken_lst, ntoken_lst->type, ntoken_lst->content, ntoken_lst->next);
}

t_bool	is_word(char chr)
{
	if (chr != '<' && chr != '>' && chr != '|' && chr != ' ' && chr != '\'' && chr != '\"')
		return (true);
	return (false);
}

void	infile_or_heredoc(t_token *token, unsigned int *idx)
{
	if (g_data.input[*idx + 1] == '<')
	{
		token->type = HEREDOC;
		*idx += 2;
	}
	else
	{
		token->type = INFILE;
		*idx  += 1;
	}
}

void	outfile_or_append(t_token *token, unsigned int *idx)
{
	if (g_data.input[*idx + 1] == '>')
	{
		token->type = APPEND;
		*idx += 2;
	}
	else
	{
		token->type = OUTFILE;
		*idx  += 1;
	}
}

t_bool	is_pipe(t_token *token, unsigned int *idx)
{
	if (g_data.input[*idx] == '|')
	{
		token->type = PIPE;
		*idx += 1;
		return (true);
	}
	return (false);
}

char	*set_content(t_token *token, unsigned int *idx)
{
	unsigned int	sub_idx;
	int				size;
	char			*content;

	sub_idx = *idx;
	size = 0;
	content = NULL;
	if (g_data.input[*idx] == '$')
	{
		size++;
		sub_idx++;
		while (ft_isalnum(g_data.input[sub_idx]) || g_data.input[sub_idx] == '_')
		{
			size++;
			sub_idx++;
		}
		printf("size = %u\n", size);
	}
	else if (is_word(g_data.input[*idx]))
	{
		size++;
		sub_idx++;
		while (is_word(g_data.input[sub_idx]) && g_data.input[sub_idx] != '\0'  \
 				&& *idx + size < ft_strlen(g_data.input) && g_data.input[sub_idx] != '$') {
			size++;
			sub_idx++;
		}
	}
	else if (g_data.input[*idx] == '\"' || g_data.input[*idx] == '\'')
	{
		while (g_data.input[sub_idx] != '\0'  \
				&& *idx + size < ft_strlen(g_data.input)) {
			size++;
			sub_idx++;
			if (g_data.input[sub_idx] == '\'' || g_data.input[sub_idx] == '\"')
			{
				size++;
				sub_idx++;
				break ;
			}
		}
	}
	printf("size = %u | sub_idx = %u\n", size, sub_idx);
	if (size == 0)
		return (NULL);
	content = garbage_alloc(&g_data.garb_lst, sizeof(char) * size + 1);
//	printf("content = %p\n", content);
	if (!content)
		return (NULL);
	ft_strlcpy(content, g_data.input + *idx, size + 1);
	*idx = *idx + size;
	return (content);
}

t_bool is_quote(t_token *token, unsigned int *idx)
{
	if (g_data.input[*idx] == '\'' || g_data.input[*idx] == '\"')
	{
		if (g_data.input[*idx] == '\'')
			token->type = SINGLE_QUOTE;
		else if (g_data.input[*idx] == '\"')
			token->type = DOUBLE_QUOTE;
		token->content = set_content(token, idx);
//		*idx += 1;
		return (true);
	}
	return (false);
}

void	space(t_token *token, unsigned int *idx)
{
	token->type = C_SPACE;
	while (g_data.input[*idx] == ' ')
		*idx += 1;
}

void	word(t_token *token, unsigned int *idx)
{
	token->type = COMMAND;
	token->content = set_content(token, idx);
}

void	variable_token(t_token *token, unsigned int *idx)
{
	token->type = VARIABLE;
	token->content = set_content(token, idx);
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
		return ;
	else if (is_quote(token, idx))
		return ;
	else if (g_data.input[*idx] == ' ')
		space(token, idx);
	else if (g_data.input[*idx] == '$')
		variable_token(token, idx);
	else if (is_word(g_data.input[*idx]))
		word(token, idx);
}

void n_lexer(void)
{
	t_token *token;
	unsigned int idx;

	idx = 0;
	while (idx < ft_strlen(g_data.input))
	{
		token = new_ntoken(&g_data.garb_lst);
		set_ntoken(token, &idx);
		printf("case = %p | type = %i | content = %s | idx = %d\n", token, token->type, token->content, idx);
		ntoken_add_back(&g_data.nlexer_lst, token);
//		sleep(1);
	}
	print_lst(g_data.nlexer_lst);
}

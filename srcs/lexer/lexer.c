#include "../../headers/lexer.h"

extern t_data g_data;

// ---------- OLD LEXER ---------- //
//void	init_token(t_token *token)
//{
//	token->type = NONE;
//	token->content = NULL;
//	token->is_closed = true;
//	token->next = NULL;
//}
//
//char	*set_content(char *input, unsigned int *idx, t_token *token)
//{
//	unsigned int	sub_idx;
//	int	size;
//	char			*content;
////	extern t_data	g_data;
//
//	sub_idx = *idx;
//	size = 0;
//	content = NULL;
//	while (input[sub_idx] != '>' && input[sub_idx] != '<' && input[sub_idx] != '|' && input[sub_idx] != '\0'  \
//	&& *idx + size < ft_strlen(input))
//	{
//	    size++;
//	    sub_idx++;
//	}
////	printf("size = %u | sub_idx = %u\n", size, sub_idx);
//	if (size == 0)
//		return (NULL);
//	content = garbage_alloc(&g_data.garb_lst, (int)sizeof(char) * (size + 1));
////	printf("content = %p\n", content);
//	if (!content)
//		return (NULL);
//	ft_strlcpy(content, input + *idx, size + 1);
//	*idx = *idx + size;
//	return (content);
//}
//
//void	input_or_heredoc(char *input, unsigned int *idx, t_token *token)
//{
////	printf("1 idx = %u\n", *idx); // TODO remove
//	if (ft_isprint(input[*idx + 1]))
//	{
//		*idx += 1;
//		if (input[*idx] == '<')
//		{
//			token->type = HEREDOC;
//			*idx += 1;
//		}
////		printf("2 idx = %u\n", *idx); // TODO remove
//		if (ft_isprint(input[*idx]))
//		{
//			token->content = set_content(input, idx, token);
////			while (input[*idx] == ' ' || ft_isalnum(input[*idx]))
////				*idx += 1;
////			printf("3 midx = %u\n", *idx); //TODO remove
//		}
//	}
//}
//
//void	output_or_append(char *input, unsigned int *idx, t_token *token)
//{
//	if (ft_isprint(input[*idx + 1]))
//	{
//		*idx += 1;
//		if (input[*idx] == '>')
//		{
//			token->type = APPEND;
//			*idx += 1;
//		}
//		if (ft_isprint(input[*idx + 1]))
//		{
//			token->content = set_content(input, idx, token);
////			while (input[*idx] == ' ' || ft_isalnum(input[*idx]))
////				*idx += 1;
//		}
//	}
//}
//
//void	pass_cmd(char *input, unsigned int *idx, t_token *token)
//{
//	token->content = set_content(input, idx, token);
////	while (ft_isalnum(input[*idx]))
////		*idx += 1;
//}
//
//t_bool	single_or_double_quote(char *input, unsigned int *idx, t_token *token)
//{
//	if (input[*idx] == '\'')
//	{
//		token->type = SINGLE_QUOTE;
//		return (true);
//	}
//	else if (input[*idx] == '\"')
//	{
//		token->type = DOUBLE_QUOTE;
//		return (true);
//	}
//	return (false);
//}
//
//void	content_quote(char *input, unsigned int *idx, t_token *token)
//{
//	char quote;
//
//	quote = input[*idx];
//	*idx+=1;
//	while (input[*idx] != '\0')
//	{
//		if (input[*idx] == quote)
//		{
//			token->is_closed = true;
//			*idx+=1;
//			return;
//		}
//		*idx+=1;
//	}
//}
//
//t_bool	ft_bandage(char chr)
//{
//	if (chr == '>' || chr == '<' || chr == '|' || \
//		ft_isalnum(chr) || chr == '\'' || chr == '\"')
//		return (true);
//	return (false);
//}
//
//void	set_token(char *input, unsigned int *idx, t_token *token)
//{
//	unsigned int tmp_idx = *idx;
//	if (input[*idx] == '<')
//	{
//		token->type = INFILE;
//		input_or_heredoc(input, idx, token);
//	}
//	else if (input[*idx] == '>')
//	{
//		token->type = OUTFILE;
//		output_or_append(input, idx, token);
//	}
//	else if (input[*idx] == '|')
//	{
//		token->type = PIPE;
//	}
//	else if (ft_isalnum(input[*idx]))
//	{
//		token->type = COMMAND;
//		pass_cmd(input, idx, token);
//	}
//	else if (single_or_double_quote(input, idx, token))
//	{
//		token->is_closed = false;
//		content_quote(input, idx, token);
//	}
////	printf("4 idx = %u | operateur = %c\n", *idx, input[*idx]); // TODO remove
//	if (ft_bandage(input[*idx]) && tmp_idx != *idx)
//		*idx -= 1;
//}
//
//void p_lex_lst(t_token *lst)
//{
//	printf("case = %p\ntype = %d\ncontent = %s\nis_closed = %d\nnext =%p\n\n", lst, lst->type, lst->content, lst->is_closed, lst->next);
//}
//
//void lexer(t_data *data)
//{
//	t_token *tmp_content;
//	unsigned int	idx;
//
//	idx = 0;
//	while (idx < strlen(data->input))
//	{
//		tmp_content = new_token(&data->garb_lst);
//		init_token(tmp_content);
//		while (data->input[idx] == ' ')
//			idx++;
//		set_token(data->input, &idx, tmp_content);
//		idx++;
//		printf("case = %p | type = %i | content = %s | is_closed = %d | idx = %d\n", tmp_content, tmp_content->type, tmp_content->content, tmp_content->is_closed, idx);
//		token_add_back(&data->lexer_lst, tmp_content);
//	}
//}
// ---------- END ---------- //

// ---------- NEW LEXER ---------- //

void	print_lst(t_ntoken *ntoken_lst)
{
	if (ntoken_lst == NULL)
		return ;
	while (ntoken_lst->next != NULL)
	{
		printf("case = %p | type = %d\n", ntoken_lst, ntoken_lst->type);
		ntoken_lst = ntoken_lst->next;
	}
	printf("case = %p | type = %d\n", ntoken_lst, ntoken_lst->type);
}

t_bool	is_word(char chr)
{
	if (chr != '<' && chr != '>' && chr != '|' && chr != ' ')
		return (true);
	return (false);
}

void	infile_or_heredoc(t_ntoken *token, unsigned int *idx)
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

void	outfile_or_append(t_ntoken *token, unsigned int *idx)
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

t_bool	is_pipe(t_ntoken *token, unsigned int *idx)
{
	if (g_data.input[*idx] == '|')
	{
		token->type = PIPE;
		*idx += 1;
		return (true);
	}
	return (false);
}

t_bool is_quote(t_ntoken *token, unsigned int *idx)
{
	if (g_data.input[*idx] == '\'' || g_data.input[*idx] == '\"')
	{
		if (g_data.input[*idx] == '\'')
			token->type = SINGLE_QUOTE;
		else if (g_data.input[*idx] == '\"')
			token->type = DOUBLE_QUOTE;
		*idx += 1;
		return (true);
	}
	return (false);
}

void	space(t_ntoken *token, unsigned int *idx)
{
	token->type = C_SPACE;
	while (g_data.input[*idx] == ' ')
		*idx += 1;
}

void	word(t_ntoken *token, unsigned int *idx)
{
	token->type = WORD;
	while (is_word(g_data.input[*idx]) && g_data.input[*idx] != '\0')
	{
		*idx += 1;
	}
}

void	set_ntoken(t_ntoken *token, unsigned int *idx)
{
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
	else if (is_word(g_data.input[*idx]))
		word(token, idx);
}

void n_lexer(void)
{
	t_ntoken *token;
	unsigned int idx;

	idx = 0;
	while (idx < ft_strlen(g_data.input))
	{
		token = new_ntoken(&g_data.garb_lst);
		set_ntoken(token, &idx);
		printf("case = %p | type = %i | content = %s | is_closed = %d | idx = %d\n", token, token->type, token->content, token->is_closed, idx);
		ntoken_add_back(&g_data.nlexer_lst, token);
//		sleep(2);
//		while (g_data.input[idx] == ' ')
//			idx++;
	}
	print_lst(g_data.nlexer_lst);
}

// ---------- END ---------- //
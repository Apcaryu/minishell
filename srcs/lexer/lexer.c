#include "../../headers/lexer.h"

void	init_token(t_token *token)
{
	token->type = NONE;
	token->content = NULL;
	token->is_closed = true;
}

void	input_or_heredoc(char *input, unsigned int *idx, t_token *token)
{
//	printf("1 idx = %u\n", *idx); // TODO remove
	if (ft_isprint(input[*idx + 1]))
	{
		*idx += 1;
		if (input[*idx] == '<')
		{
			token->type = HEREDOC;
			*idx += 1;
		}
//		printf("2 idx = %u\n", *idx); // TODO remove
		if (ft_isprint(input[*idx]))
		{
			while (input[*idx] == ' ' || ft_isalnum(input[*idx]))
				*idx += 1;
//			printf("3 midx = %u\n", *idx); //TODO remove
		}
	}
}

void	output_or_append(char *input, unsigned int *idx, t_token *token)
{
	if (ft_isprint(input[*idx + 1]))
	{
		*idx += 1;
		if (input[*idx] == '>')
		{
			token->type = APPEND;
			*idx += 1;
		}
		if (ft_isprint(input[*idx + 1]))
		{
			while (input[*idx] == ' ' || ft_isalnum(input[*idx]))
				*idx += 1;
		}
	}
}

void	pass_cmd(char *input, unsigned int *idx, t_token *token)
{
	while (ft_isalnum(input[*idx]))
		*idx += 1;
}

t_bool	single_or_double_quote(char *input, unsigned int *idx, t_token *token)
{
	if (input[*idx] == '\'')
	{
		token->type = SINGLE_QUOTE;
		return (true);
	}
	else if (input[*idx] == '\"')
	{
		token->type = DOUBLE_QUOTE;
		return (true);
	}
	return (false);
}

void	content_quote(char *input, unsigned int *idx, t_token *token)
{
	char quote;

	quote = input[*idx];
	*idx+=1;
	while (input[*idx] != '\0')
	{
		if (input[*idx] == quote)
		{
			token->is_closed = true;
			*idx+=1;
			return;
		}
		*idx+=1;
	}
}

t_bool	ft_bandage(char chr)
{
	if (chr == '>' || chr == '<' || chr == '|' || \
		ft_isalnum(chr) || chr == '\'' || chr == '\"')
		return (true);
	return (false);
}

void	set_token(char *input, unsigned int *idx, t_token *token)
{
	unsigned int tmp_idx = *idx;
	if (input[*idx] == '<')
	{
		token->type = INPUT;
		input_or_heredoc(input, idx, token);
	}
	else if (input[*idx] == '>')
	{
		token->type = OUTPUT;
		output_or_append(input, idx, token);
	}
	else if (input[*idx] == '|')
	{
		token->type = PIPE;
	}
	else if (ft_isalnum(input[*idx]))
	{
		token->type = COMMAND;
		pass_cmd(input, idx, token);
	}
	else if (single_or_double_quote(input, idx, token))
	{
		token->is_closed = false;
		content_quote(input, idx, token);
	}
//	printf("4 idx = %u | operateur = %c\n", *idx, input[*idx]); // TODO remove
	if (ft_bandage(input[*idx]) && tmp_idx != *idx)
		*idx -= 1;
}

void lexer(char *input)
{
	t_token tmp_content;
	unsigned int	idx;

	idx = 0;
	init_token(&tmp_content);
	while (idx < strlen(input))
	{
		while (input[idx] == ' ')
			idx++;
		set_token(input, &idx, &tmp_content);
		idx++;
		printf("type = %i | content = %s | is_closed = %d | idx = %d\n", tmp_content.type, tmp_content.content, tmp_content.is_closed, idx);
		init_token(&tmp_content);
	}
}

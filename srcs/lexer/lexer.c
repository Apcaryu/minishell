#include "../../headers/lexer.h"

void	init_token(t_token *token)
{
	token->type = NONE;
	token->content = NULL;
}

void	input_or_heredoc(char *input, unsigned int *idx, t_token *token)
{
	if (ft_isprint(input[*idx + 1]))
	{
		*idx += 1;
		if (input[*idx] == '<')
			token->type = HEREDOC;
		*idx += 1;
		if (ft_isprint(input[*idx + 1]))
		{
			while (input[*idx] == ' ' || ft_isalnum(input[*idx]))
				*idx += 1;
		}
	}
}

void	set_token(char *input, unsigned int *idx, t_token *token)
{
	if (input[*idx] == '<')
	{
		token->type = INPUT;
		input_or_heredoc(input, idx, token);
	}
}

void lexer(char *input)
{
	t_token tmp_content;
	unsigned int	idx;

	idx = 0;
	init_token(&tmp_content);
	while (idx < strlen(input))
	{
		while (input[idx] == ' ' || ft_isalnum(input[idx]))
			idx++;
		set_token(input, &idx, &tmp_content);
		idx++;
		printf("type = %i | content = %s | idx = %d\n", tmp_content.type, tmp_content.content, idx);
		init_token(&tmp_content);

	}
}

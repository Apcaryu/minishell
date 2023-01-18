#include "../headers/expend.h"

extern t_data g_data;

char	*le_set_content(t_token *token, char *input, unsigned int *idx)
{
	unsigned int	sub_idx;
	int				size;
	char			*content;

	sub_idx = *idx;
	size = 0;
	content = NULL;
	while (input[*idx] == ' ' && input[*idx] != '\0')
	{
		token->type = C_SPACE;
		*idx += 1;
	}
	if(token->type == C_SPACE)
		return (NULL);
	while (input[sub_idx] != ' ' && input[sub_idx] != '\0')
	{
		size++;
		sub_idx++;
	}
//	printf("size = %u | sub_idx = %u\n", size, sub_idx);
	if (size == 0)
		return (input);
	content = garbage_alloc(&g_data.garb_lst, sizeof(char) * size + 1);
//	printf("content = %p\n", content);
	if (!content)
		return (input);
	ft_strlcpy(content, input + *idx, size + 1);
	*idx = *idx + size;
	return (content);
}

t_token	*lex_expend(char *input, t_token *token_start)
{
	t_token *new;
	t_token *tmp;
	t_token *token_end;
	unsigned int idx;

	idx = 0;
	token_end = token_start->next;
//	token_start->next = NULL;
	printf("token_end = %p\n", token_end);
	printf("len = %zu\n", ft_strlen(input));
	while (idx < ft_strlen(input))
	{
		printf("idx = %u\n", idx);
		new = new_token(&g_data.garb_lst);
		new->type = COMMAND;
		new->content = le_set_content(new, input, &idx);
		if (new != NULL) {
			if (token_start->next == token_end) {
				token_start->next = new;
//				new->next = token_end;
				token_start = new;
				token_start->next = token_end;
			}
//			token_add_back(&token_start, new);
		}
//		sleep(1);
	}
	return (token_start);
}
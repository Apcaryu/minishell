/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:01:09 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/09 14:01:11 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/expend.h"

extern t_data	g_data;

int	word_size(char *input, unsigned int idx)
{
	unsigned int	sub_idx;
	int				size;

	sub_idx = idx;
	size = 0;
	while (input[sub_idx] != ' ' && input[sub_idx] != '\0')
	{
		size++;
		sub_idx++;
	}
	return (size);
}

char	*le_set_content(t_token *token, char *input, unsigned int *idx)
{
	int				size;
	char			*content;

	content = NULL;
	while (input[*idx] == ' ')
	{
		token->type = C_SPACE;
		*idx += 1;
	}
	if (token->type == C_SPACE)
		return (NULL);
	else
		token->type = COMMAND;
	size = word_size(input, *idx);
	if (size == 0)
		return (input);
	content = garbage_alloc(&g_data.garb_lst, sizeof(char) * size + 1);
	if (!content)
		return (input);
	ft_strlcpy(content, input + *idx, size + 1);
	*idx = *idx + size;
	return (content);
}

t_token	*lex_expend(char *input)
{
	t_token			*out_lst;
	t_token			*new;
	unsigned int	idx;

	out_lst = NULL;
	idx = 0;
	while (idx < ft_strlen(input))
	{
		new = new_token(&g_data.garb_lst);
		new->content = le_set_content(new, input, &idx);
		token_add_back(&out_lst, new);
	}
	return (out_lst);
}

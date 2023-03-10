/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:46:52 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/08 13:46:54 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"

int	size_of_var(char *input, unsigned int idx)
{
	unsigned int	sub_idx;
	int				size_out;

	sub_idx = idx + 1;
	size_out = 1;
	if (input[sub_idx] == '?')
		return (2);
	while (ft_isalnum(input[sub_idx]) || input[sub_idx] == '_')
	{
		size_out++;
		sub_idx++;
	}
	return (size_out);
}

int	size_of_word(char *input, unsigned int idx)
{
	unsigned int	sub_idx;
	int				size_out;

	sub_idx = idx + 1;
	size_out = 1;
	while (is_word(input[sub_idx]) && input[sub_idx] != '\0' && \
	idx + size_out < ft_strlen(input) && input[sub_idx] != '$')
	{
		size_out++;
		sub_idx++;
	}
	return (size_out);
}

int	size_of_quote(char *input, unsigned int idx, char type_quote)
{
	unsigned int	sub_idx;
	int				size_out;

	sub_idx = idx;
	size_out = 0;
	while (input[sub_idx] != '\0' && idx + size_out < ft_strlen(input))
	{
		size_out++;
		sub_idx++;
		if (input[sub_idx] == type_quote)
		{
			size_out++;
			break ;
		}
	}
	return (size_out);
}

char	*set_content(t_data *data, unsigned int *idx)
{
	int				size;
	char			*content;

	size = 0;
	content = NULL;
	if (data->input[*idx] == '$')
		size = size_of_var(data->input, *idx);
	else if (is_word(data->input[*idx]))
		size = size_of_word(data->input, *idx);
	else if (data->input[*idx] == '\"' || data->input[*idx] == '\'')
		size = size_of_quote(data->input, *idx, data->input[*idx]);
	if (size == 0)
		return (NULL);
	content = garbage_alloc(&data->garb_lst, sizeof(char) * size + 1);
	if (!content)
		return (NULL);
	ft_strlcpy(content, data->input + *idx, size + 1);
	*idx = *idx + size;
	return (content);
}

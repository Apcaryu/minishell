/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:16:34 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/08 14:16:36 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"

void	set_token(t_data *data, t_token *token, unsigned int *idx)
{
	if (data->input[*idx] == '<')
		infile_or_heredoc(token, idx);
	else if (data->input[*idx] == '>')
		outfile_or_append(token, idx);
	else if (is_pipe(token, idx))
		return ;
	else if (is_quote(idx))
		quote(data, token, idx);
	else if (data->input[*idx] == ' ')
		space(token, idx);
	else if (data->input[*idx] == '$')
		variable_token(data, token, idx);
	else if (is_word(data->input[*idx]))
		word(data, token, idx);
}

void	lexer(t_data *data)
{
	t_token			*token;
	unsigned int	idx;

	idx = 0;
	while (idx < ft_strlen(data->input))
	{
		token = new_token(&data->garb_lst);
		set_token(data, token, &idx);
		token_add_back(&data->lexer_lst, token);
	}
	print_lst(data->lexer_lst);
}

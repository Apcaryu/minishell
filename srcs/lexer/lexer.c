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

extern t_data	g_data;

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
		quote(token, idx) ;
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

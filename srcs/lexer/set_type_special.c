/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:36:43 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/08 13:36:44 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"

extern t_data	g_data;

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
		*idx += 1;
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
		*idx += 1;
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

void	quote(t_data *data, t_token *token, unsigned int *idx)
{
	if (g_data.input[*idx] == '\'')
		token->type = SINGLE_QUOTE;
	else if (g_data.input[*idx] == '\"')
		token->type = DOUBLE_QUOTE;
	token->content = set_content(data, idx);
}

void	variable_token(t_data *data, t_token *token, unsigned int *idx)
{
	token->type = VARIABLE;
	token->content = set_content(data, idx);
}

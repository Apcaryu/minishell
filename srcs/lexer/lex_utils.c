/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:07:49 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/17 15:59:30 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"

t_bool	is_word(char chr)
{
	if (chr != '<' && chr != '>' && chr != '|' && chr != ' ' && chr != '\'' \
	&& chr != '\"')
		return (true);
	return (false);
}

t_bool	is_quote(char chr)
{
	if (chr == '\'' || chr == '\"')
		return (true);
	return (false);
}

t_bool	quote_closed(char *content)
{
	char			quote_type;
	unsigned int	idx;

	quote_type = content[0];
	idx = 1;
	while (content[idx] != '\0')
	{
		if (content[idx] == quote_type)
			return (true);
		idx++;
	}
	return (false);
}

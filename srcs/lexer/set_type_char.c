/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:00:12 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/08 14:00:13 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"

void	space(char *input, t_token *token, unsigned int *idx)
{
	token->type = C_SPACE;
	while (input[*idx] == ' ')
		*idx += 1;
}

void	word(t_data *data, t_token *token, unsigned int *idx)
{
	token->type = COMMAND;
	token->content = set_content(data, idx);
}

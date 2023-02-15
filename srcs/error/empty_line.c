/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:34:08 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/15 13:34:10 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/error_msg.h"

t_bool	is_space(char chr)
{
	if (chr == ' ' || chr == '\t' || chr == '\n' || chr == '\v' || chr == '\0')
		return (true);
	return (false);
}

t_bool	is_full_space(char *input)
{
	unsigned int	idx;

	idx = 0;
	while (input[idx] != '\0')
	{
		if (!is_space(input[idx]))
			return (false);
		idx++;
	}
	return (true);
}

t_bool	is_empty_line(char *input)
{
	if (input == NULL)
		return (true);
	else if (input[0] == '\0')
		return (true);
	else if (is_full_space(input))
		return (true);
	return (false);
}

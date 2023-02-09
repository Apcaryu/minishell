/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:13:47 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/09 14:13:48 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/expend.h"

t_bool	is_type_word(t_type type)
{
	if (type == COMMAND || type == SINGLE_QUOTE || type == DOUBLE_QUOTE || \
	type == VARIABLE)
		return (true);
	return (false);
}

void	init_varenv(t_varenv *varenv)
{
	varenv->var_name = NULL;
	varenv->var_content = NULL;
	varenv->var_size = 0;
	varenv->var_content_size = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:31:21 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/09 14:31:22 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/expend.h"

extern t_data	g_data;

unsigned int	detect_dollar(char *word, unsigned int idx)
{
	while (word[idx] != '\0')
	{
		if (word[idx] == '$')
			return (idx);
		idx++;
	}
	return (UINT_MAX);
}

unsigned int	variable_size(const char *str, unsigned int idx)
{
	unsigned int	len_out;

	len_out = 0;
	idx++;
	while (ft_isalnum(str[idx]) || str[idx] == '_')
	{
		idx++;
		len_out++;
	}
	return (len_out);
}

char	*variable_name(char *str, unsigned int idx, unsigned int var_size)
{
	char	*var_name;

	var_name = garbage_alloc(&g_data.garb_lst, sizeof(char) * var_size + 2);
	ft_strlcpy(var_name, str + idx, var_size + 2);
	return (var_name);
}

unsigned int	var_content_size(char *var_name)
{
	unsigned int	size;
	char			*tmp;

	tmp = getenv(var_name + 1);
	if (tmp == NULL)
		return (0);
	size = ft_strlen(tmp);
	return (size);
}

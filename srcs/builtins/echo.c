/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:29:40 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/16 15:53:16 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"

extern t_data	g_data;

void	echo_exec(void)
{
	t_bool	n;
	int		i;
	int		count_args;

	i = 1;
	count_args = 0;
	n = true;
	if (!g_data.parser_lst->args[1])
		write(1, "\n", 5);
	while (g_data.parser_lst->args[count_args])
		count_args++;
	// while (g_data.parser_lst->args[i])
	while (i < count_args)
	{
		if (i == 1 && g_data.parser_lst->args[i] && ft_strncmp(g_data.parser_lst->args[i], "-n", ft_strlen(g_data.parser_lst->args[i])) == 0)
		{
			i++;
			n = false;
		}
		write(1, g_data.parser_lst->args[i], ft_strlen(g_data.parser_lst->args[i]));
		// if (g_data.parser_lst->args[i + 1])
		if (i != count_args - 1)
			write(1, " ", 1);
		i++;
		// dprintf(2, "counter = %d\n", i);
	}
	if (n)
		write(1, "\n", 1);
}

// ! TODO : echo -n
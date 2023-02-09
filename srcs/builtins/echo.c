/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:29:40 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/09 16:22:41 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"

extern t_data	g_data;

void	echo_exec(t_elem_pars *elem)
{
	t_bool	n;
	int		i;
	int		si;
	int		count_args;

	i = 1;
	si = i;
	count_args = 0;
	n = true;
	if (!elem->args[1])
		write(1, "\n", 1);
	while (elem->args[count_args])
		count_args++;
	while (i < count_args)
	{
		if (i == 1 && elem->args[i][0] == '-')
		{
			si++;
			while (elem->args[i][si] == 'n')
			{
				si++;
			}
			if (elem->args[i][si] == ' ' || elem->args[i][si] == '\0')
			{
				i++;
				n = false;
			}
		}
		if (elem->args[i] != NULL)
		{
			write(1, elem->args[i], ft_strlen(elem->args[i]));
			if (i != count_args - 1)
				write(1, " ", 1);
		}
		i++;
	}
	if (n)
		write(1, "\n", 1);
}

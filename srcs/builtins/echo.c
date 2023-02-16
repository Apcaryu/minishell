/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:29:40 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 07:02:28 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"

extern t_data	g_data;

void	echo_utils_bis(t_elem_pars *elem, int count_args, int i)
{
	write(1, elem->args[i], ft_strlen(elem->args[i]));
	if (i != count_args - 1)
		write(1, " ", 1);
}

t_bool	echo_utils(t_elem_pars *elem, int count_args, t_bool n, int i)
{
	int		si;
	int		count;
	t_bool	check;

	count = 1;
	while (++i < count_args)
	{
		check = true;
		if (elem->args[i][0] == '-')
		{
			si = 1;
			while (elem->args[i][si] == 'n')
				si++;
			if (count == i && si != 1 && (elem->args[i][si] == ' '
				|| elem->args[i][si] == '\0'))
			{
				count++;
				n = false;
				check = false;
			}
		}
		if (check == true && elem->args[i] != NULL)
			echo_utils_bis(elem, count_args, i);
	}
	return (n);
}

void	echo_exec(t_elem_pars *elem)
{
	t_bool	n;
	int		i;
	int		count_args;

	i = 0;
	n = true;
	count_args = 0;
	while (elem->args[count_args])
		count_args++;
	n = echo_utils(elem, count_args, n, i);
	if (n)
		write(1, "\n", 1);
}

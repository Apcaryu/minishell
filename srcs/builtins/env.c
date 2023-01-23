/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:39:56 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/16 15:53:10 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"

extern t_data	g_data;

void	env_exec(void)
{
	int i;

	i = 0;
	dprintf(2, "exec env\n");
	// if (g_data.parser_lst->args[1] != NULL)
	// 	write(2, "Env Error\n", 11);
	while (g_data.tab[i])
	{
		printf("%s\n", g_data.tab[i]);
		i++;
	}
}

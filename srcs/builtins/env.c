/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:39:56 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/15 11:29:34 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"

extern t_data	g_data;

void	env_exec(void)
{
	int	i;

	i = 0;
	if (g_data.tab[i])
	{
		while (g_data.tab[i])
		{
			printf("%s\n", g_data.tab[i]);
			i++;
		}
	}
	else
	{
		g_data.tab = garbage_alloc(&g_data.garb_lst, sizeof(char *) * 4);
		g_data.tab[0] = "PWD=/mnt/nfs/homes/meshahrv\
						/Documents/Circle_3/MINISHELL_GIT";
		g_data.tab[1] = "SHLVL=1";
		g_data.tab[2] = "_=/usr/bin/env";
		g_data.tab[3] = 0;
		while (g_data.tab[i])
		{
			printf("%s\n", g_data.tab[i]);
			i++;
		}
	}
}

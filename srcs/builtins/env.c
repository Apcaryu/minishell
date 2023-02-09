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
	while (g_data.tab[i])
	{
		printf("%s\n", g_data.tab[i]);
		i++;
	}
}

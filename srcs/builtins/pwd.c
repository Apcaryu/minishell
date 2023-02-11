/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:26:25 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/11 19:53:14 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"

extern t_data	g_data;

void	pwd_exec(void)
{
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	if (!getcwd(cwd, PATH_MAX))
	{
		while (g_data.tab[i] && ft_strnstr(g_data.tab[i], "PWD", 3) == 0)
			i++;
		printf("%s\n", g_data.tab[i] + 4);
	}
	else if (getcwd(cwd, PATH_MAX))
		printf("%s\n", cwd);
}
 
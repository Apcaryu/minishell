/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:26:25 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/16 18:44:58 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"

extern t_data	g_data;

void	pwd_exec(void)
{
	// printf("exec pwd\n");
	char	cwd[PATH_MAX];

	if (getcwd(cwd, ))
	printf("%s\n", )
}
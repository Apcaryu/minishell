/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:53:28 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/17 17:54:25 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"

extern t_data	g_data;

int	count_args(void)
{
	int	i;

	i = 0;
	while (g_data.parser_lst->args[i])
		i++;
	return (i);
}

void	update_pwd(void)
{
	// printf("exec cd\n");
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("pwd : ");
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return ;
	dprintf(2, "oldpwd = %s\n", oldpwd);
	free(oldpwd);
}

void	cd_exec(void)
{
	// if (count_args() <= 2)
	// {
	// 	if ()
	// 		return ;
	// }
	update_pwd();
}

// ^ $OLDPWD
/* 
	le dernier répertoire visité 
	par l'utilisateur connecté
*/ 

// ^ $PWD
/* 
	Répertoire courant
*/ 
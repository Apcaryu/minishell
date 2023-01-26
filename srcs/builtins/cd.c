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

int	count_args(t_data data)
{
	int	i;

	i = 0;
	// dprintf(2, "cd->cmd = %s\n", data.parser_lst->cmd);
	// dprintf(2, "cd->args = %s\n", data.parser_lst->args[1]);
	if (data.parser_lst->args == NULL)
	{
		i = 1;
		return (i);
	}
	while (data.parser_lst->args[i])
		i++;
	return (i);
}

void	update_pwd(void)
{
	// printf("exec cd\n");
	char	cwd[PATH_MAX];
	char	*oldpwd;

	dprintf(2, "cwd = %s\n", getcwd(cwd, PATH_MAX));
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("pwd : ");
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return ;
	export_exec(oldpwd);
	// dprintf(2, "oldpwd = %s\n", oldpwd);
	free(oldpwd);
}

void	void_cd(void)
{
	char *home = getenv("HOME"); // TODO recuperer le home de l'env de minishell

	dprintf(2, "home = %s\n", home);
	update_pwd();
	printf("chdir = %d\n", chdir(home));
}

void	cd_exec(t_elem_pars *elem)
{
	t_data	data;
	int		res;

	data = g_data;
	// --------- ONLY TEST ---------- //
	// void_cd();
	// return;
	// --------- END ---------- //
	if (elem->args[1] == NULL){
		void_cd();
		return;
	}
	if (count_args(data) <= 2)
	{
		update_pwd();
		printf("chdir = %d\n",chdir(elem->args[1]));
	}
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
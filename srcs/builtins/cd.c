/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:53:28 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 03:16:50 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"
#include "../../headers/minishell.h"

extern t_data	g_data;

int	count_args(t_data data)
{
	int	i;

	i = 0;
	if (data.parser_lst->args == NULL)
	{
		i = 1;
		return (i);
	}
	while (data.parser_lst->args[i])
		i++;
	return (i);
}

void	update_pwd(t_elem_pars *elem)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*new_pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("pwd : ");
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX));
	if (!oldpwd)
		return ;
	if (chdir(elem->args[1]))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(elem->args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	new_pwd = ft_strjoin("PWD=", getcwd(cwd, PATH_MAX));
	export_exec(new_pwd);
	free(new_pwd);
	export_exec(oldpwd);
	free(oldpwd);
}

void	void_cd(t_elem_pars *elem)
{
	int	i;

	i = 0;
	while (g_data.tab[i])
	{
		if (ft_strnstr(g_data.tab[i], "HOME", 4))
		{
			update_pwd(elem);
			chdir(g_data.tab[i] + 5);
			break ;
		}
		i++;
	}
	if (g_data.tab[i] == NULL)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
}

void	cd_exec(t_elem_pars *elem)
{
	t_data	data;

	data = g_data;
	if (elem->args[1] == NULL)
	{
		void_cd(elem);
		return ;
	}
	if (count_args(data) <= 2)
		update_pwd(elem);
	else
		error_msgs(elem->args[0], "too many arguments\n");
}

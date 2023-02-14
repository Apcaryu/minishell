/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:53:28 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/14 16:18:33 by meshahrv         ###   ########.fr       */
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

void	update_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("pwd : ");
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX));
	if (!oldpwd)
		return ;
	export_exec(oldpwd);
	free(oldpwd);
}

void	void_cd(void)
{
	int	i;

	i = 0;
	while (g_data.tab[i])
	{
		if (ft_strnstr(g_data.tab[i], "HOME", 4))
		{
			update_pwd();
			chdir(g_data.tab[i] + 5);
			break ;
		}
		i++;
		if (g_data.tab[i] == NULL)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
}

void	cd_exec(t_elem_pars *elem)
{
	t_data	data;
	int		res;

	data = g_data;
	if (elem->args[1] == NULL)
	{
		void_cd();
		return ;
	}
	if (count_args(data) <= 2)
	{
		update_pwd();
		chdir(elem->args[1]);
	}
	if (count_args(data) > 2)
		error_msgs(elem->args[0], "too many arguments\n");
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(elem->args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}			
}

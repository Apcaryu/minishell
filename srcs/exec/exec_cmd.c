/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:24:01 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 15:56:17 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

char	**get_env(void)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	while (g_data.tab && g_data.tab[i] \
		&& !ft_strnstr(g_data.tab[i], "PATH=", 5))
		i++;
	if (g_data.tab[i] == NULL)
		return (NULL);
	tab = ft_split(g_data.tab[i] + 5, ':');
	return (tab);
}

void	path_is_null(t_elem_pars *start)
{
	int		access_out;

	access_out = -1;
	if (*start->args != NULL)
		access_out = access(*start->args, X_OK);
	if (access_out != 0)
	{
		error_msgs(start->cmd, "No such file or directory\n");
		ft_lstclear(&g_data.garb_lst, &free);
		exit(127);
	}
	else
	{
		error_msgs(*start->args, "command not found\n");
		ft_lstclear(&g_data.garb_lst, &free);
		exit(127);
	}
}

void	path_exist(char **tab, t_elem_pars *start, t_exec *exec)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (tab[i])
	{
		tmp = ft_strjoin(tab[i], "/");
		path = ft_strjoin(tmp, start->cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			exec->exit_code = execve(path, start->args, g_data.tab);
			if (exec->exit_code == -1)
			{
				perror("execve: ");
				exit(127);
			}
		}
		free(path);
		i++;
	}
}

void	exec_path(t_elem_pars *start, t_exec *exec)
{
	char	**tab;

	tab = NULL;
	tab = get_env();
	if (tab == NULL)
		path_is_null(start);
	path_exist(tab, start, exec);
	error_msgs(start->cmd, "command not found\n");
	clean_cmds(tab);
	ft_lstclear(&g_data.garb_lst, &free);
	g_data.exit_code = 127;
	exit(127);
}

void	exec_cmd(t_exec *exec, t_elem_pars *start, t_elem_pars *elem)
{
	int	access_out;

	access_out = -1;
	while (((elem->next != NULL && start != elem) \
		|| (elem->next == NULL && start != NULL)) \
		&& start->type != COMMAND)
	{
		start = start->next;
	}
	if (start->cmd != NULL)
		access_out = access(start->cmd, F_OK);
	if (access_out == 0)
		execve(start->cmd, elem->args, g_data.tab);
	if (start && start->type == COMMAND)
		exec_path(start, exec);
	exit(0);
}

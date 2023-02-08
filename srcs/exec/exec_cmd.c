/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:24:01 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/08 19:19:04 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

char	**get_env(t_exec *exec)
{
	int		i;
	char	**tab;
	// extern char	*environ;
	i = 0;
	while (g_data.tab[i] && ft_strnstr(g_data.tab[i], "PATH", 4) == 0)
		i++;
	if (g_data.tab[i] == NULL)
		return (NULL);
	tab = ft_split(g_data.tab[i] + 5, ':');
	return (tab);
}

// void	env_is_null(t_elem_pars *start)
// {
// 	if (*start->args != NULL)
// 		access(*start->args, X_OK);
// 	else
// 	{
// 		error_msgs(*start->args, "command not found\n");
// 		clean_cmds(start->args);
// 		exit(127);
// 	}
// }

void	exec_path(t_elem_pars *start, t_exec *exec)
{
	int		i;
	char	*tmp;
	char	**tab;
	char	*path;
	int		access_out;

	i = 0;
	access_out = -1;
	tab = get_env(exec);
	if (tab == NULL)
	{
		dprintf(2, "ENV EST NULLLLLLL\n");
		// env_is_null(start);
		if (*start->args != NULL)
			access_out = access(*start->args, X_OK);
		if (access_out != 0)
		{
			error_msgs(start->cmd, "command not found\n");
			exit(127);
		}
		else
		{
			error_msgs(*start->args, "command not found\n");
			clean_cmds(start->args);
			exit(127);
		}
	}
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
	if (ft_isalnum(start->cmd[0]))
		error_msgs(start->cmd, "command not found\n");
	clean_cmds(tab);
	clean_cmds(start->args);
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
		if (start == NULL)
		{
			// dprintf(2, "BLABLABLABLA\n");
			exit (127);
		}
	}
	if (start->cmd != NULL)
		access_out = access(start->cmd, F_OK);
	if (access_out == 0)
		execve(start->cmd, elem->args, g_data.tab);
	if (start && start->type == COMMAND)
		exec_path(start, exec);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:24:01 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/18 16:42:27 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

char	**get_env(t_exec *exec)
{
	int i;
	char	**tab;

	i = 0;
	while (ft_strnstr(g_data.env[i], "PATH", 4) == 0)
		i++;
	tab = ft_split(g_data.env[i] + 5, ':');
	if (tab == NULL)
		return (NULL);
	return (tab);
}

void	exec_path(t_elem_pars *start, t_exec *exec)
{
	int		i;
	int		j;
	char	*tmp;
	char 	**tab;
	char	*path;
	
	i = 0;
	j = 0;
	tab = get_env(exec);
	if (tab == NULL)
	{
		if (*start->args != NULL)
			access(*start->args, X_OK);
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
			exec->exit_code = execve(path, start->args, g_data.env);
			if (exec->exit_code == -1)
				perror("execve: ");
		}
		free(path);
		i++;
	}
	error_msgs(start->cmd, "command not found\n");
	clean_cmds(tab);
	clean_cmds(start->args);
	exit(127);
}

void exec_cmd(t_exec *exec, t_elem_pars *start, t_elem_pars *elem)
{
	int access_out;
	
	access_out = -1;
	while (((elem->next != NULL && start != elem) || (elem->next == NULL && start != NULL)) && start->type != COMMAND)
	{
		start = start->next;
		if (start == NULL)
			return;
	}
	// dprintf(2, "*exec->cmds = %s\n", *exec->cmds);
	// if (start->cmd != NULL)
	// 	access_out = access(start->cmd, F_OK);
	// if (access_out == 0)
	// 	execve("/bin/", elem->args, NULL /*g_data.env*/);
	if (start->type == COMMAND)
		exec_path(start, exec);
	// exit (127);
}

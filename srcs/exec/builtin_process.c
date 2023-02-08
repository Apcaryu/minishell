/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:17:03 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/08 16:20:08 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

t_bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strncmp("echo", cmd, ft_strlen("echo")) == 0
		|| ft_strncmp("env", cmd, ft_strlen("env")) == 0 \
		|| ft_strncmp("export", cmd, ft_strlen("export")) == 0 \
		|| ft_strncmp("pwd", cmd, ft_strlen("pwd")) == 0 \
		|| ft_strncmp("exit", cmd, ft_strlen("exit")) == 0 \
		|| ft_strncmp("cd", cmd, ft_strlen("cd")) == 0 \
		|| ft_strncmp("unset", cmd, ft_strlen("unset")) == 0)
		return (true);
	return (false);
}

t_bool	check_all_builtin(t_elem_pars *elem)
{
	while (elem != NULL)
	{
		if (is_builtin(elem->cmd))
			return (true);
		elem = elem->next;
	}
	return (false);
}

void	builtin_process(t_exec *exec, t_elem_pars *elem)
{
	int	i;

	while (elem != NULL)
	{
		if (elem->type == COMMAND && !ft_strncmp("echo", elem->cmd, ft_strlen("echo")))
			echo_exec(elem);
		else if (elem->type == COMMAND && !ft_strncmp("env", elem->cmd, ft_strlen("env")))
			env_exec();
		else if (elem->type == COMMAND && !ft_strncmp("pwd", elem->cmd, ft_strlen("pwd")))
			pwd_exec();
		else if (elem->type == COMMAND && !ft_strncmp("cd", elem->cmd, ft_strlen("cd")))
			cd_exec(elem);
		else if (elem->type == COMMAND && !ft_strncmp("exit", elem->cmd, ft_strlen("exit")))
			exit_exec(exec);
		else if (elem->type == COMMAND && !ft_strncmp("export", elem->cmd, ft_strlen("export")))
		{
			i = 1;
			while (elem->args[i])
			{
				export_exec(elem->args[i]);
				i++;
			}
		}
		else if (elem->type == COMMAND && !ft_strncmp("unset", elem->cmd, ft_strlen("unset")))
		{
			i = 0;
			while (elem->args[i])
			{
				unset_exec(elem->args[i]);
				i++;
			}
		}
		elem = elem->next;
	}
}

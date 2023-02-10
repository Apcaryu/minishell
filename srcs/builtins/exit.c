/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:40:51 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/10 12:26:05 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"
#include "../../headers/minishell.h"

extern t_data	g_data;

void	clear_and_exit_builtin(t_data data, t_exec *exec, t_bool too_many_args)
{
	if (too_many_args == true)
		return ;
	clean_cmds(data.tab);
	free_env(data.env_bis);
	ft_lstclear(&data.garb_lst, &free);
	ft_putstr_fd("exit\n", 2);
	exit(exec->exit_code);
}

t_bool	exit_process(t_exec *exec, unsigned long long int idx, \
						t_bool too_many_args)
{
	if (g_data.parser_lst->args[1][idx] == '-')
		idx++ ;
	while (idx < ft_strlen(g_data.parser_lst->args[1]))
	{
		if (!ft_isdigit(g_data.parser_lst->args[1][idx]))
		{
			error_msgs(g_data.parser_lst->args[1], \
				"numeric argument required\n");
			exit(2);
		}
		idx++;
	}
	idx = 0;
	while (g_data.parser_lst->args[idx] != NULL)
	{
		if (idx == 2)
		{
			too_many_args = true;
			error_msgs(g_data.parser_lst->cmd, "too many arguments\n");
			return (too_many_args);
		}
		idx++;
	}
	exec->exit_code = ft_atoi(g_data.parser_lst->args[1]);
	return (too_many_args);
}

void	exit_exec(t_exec *exec)
{
	unsigned long long int	idx;
	t_bool					too_many_args;

	idx = 0;
	too_many_args = false;
	if (!g_data.parser_lst->args)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (g_data.parser_lst->args[1])
		too_many_args = exit_process(exec, idx, too_many_args);
	clear_and_exit_builtin(g_data, exec, too_many_args);
}

// TODO :  changer atoi, long long int
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:40:51 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 07:18:41 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"
#include "../../headers/minishell.h"

extern t_data	g_data;

long long int	ft_atol(const char *str)
{
	int				i;
	int				sign;
	long long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 8 && str[i] <= 13) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * res);
}

void	clear_and_exit_builtin(t_data data, int exit_code)
{
	ft_lstclear(&data.garb_lst, &free);
	ft_putstr_fd("exit\n", 2);
	exit(exit_code);
}

void	end_exit(void)
{
	int	tmp;

	tmp = ft_atol(g_data.parser_lst->args[1]);
	ft_lstclear(&g_data.garb_lst, &free);
	exit(tmp);
}

t_bool	exit_process(unsigned long long int idx, \
						t_bool too_many_args)
{
	if (g_data.parser_lst->args[1][idx] == '-')
		idx++ ;
	while (idx < ft_strlen(g_data.parser_lst->args[1]))
	{
		if (!ft_isdigit(g_data.parser_lst->args[1][idx]))
		{
			error_msgs(g_data.parser_lst->args[1], NAR);
			ft_lstclear(&g_data.garb_lst, &free);
			exit(2);
		}
		idx++;
	}
	idx = -1;
	while (g_data.parser_lst->args[++idx] != NULL)
	{
		if (idx == 2)
		{
			too_many_args = true;
			error_msgs(g_data.parser_lst->cmd, TMA);
			return (too_many_args);
		}
	}
	end_exit();
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
		too_many_args = exit_process(idx, too_many_args);
	if (too_many_args == true)
		return ;
	clear_and_exit_builtin(g_data, exec->exit_code);
}

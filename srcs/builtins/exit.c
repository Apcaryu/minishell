/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:40:51 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/17 16:17:09 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"
#include "../../headers/minishell.h"

extern t_data	g_data;

void	exit_exec(t_exec *exec)
{
	unsigned long long int idx;
	
	idx = 0;
	// dprintf(2, "ICI == %p\n", g_data.parser_lst->args);
	if (!g_data.parser_lst->args)
	{
		printf("exit\n");
		exit(0);
	}
	if (g_data.parser_lst->args[1])
	{
		printf("exit\n");
		if (g_data.parser_lst->args[1][idx] == '-')
			idx++ ;
		while (idx < ft_strlen(g_data.parser_lst->args[1]))
		{
			if (!ft_isdigit(g_data.parser_lst->args[1][idx]))
			{
				error_msgs(g_data.parser_lst->args[1], "numeric argument required\n");
				exit(2);
			}
			idx++;
		}
		idx = 0;
		while (g_data.parser_lst->args[idx] != NULL)
		{
			if (idx == 2)
			{
				error_msgs(g_data.parser_lst->cmd, "too many arguments\n");
				return ;
			}
			idx++;
		}
		exec->exit_code = ft_atoi(g_data.parser_lst->args[1]);
	}
	exit(exec->exit_code);
}

// TODO :  changer atoi, long long int
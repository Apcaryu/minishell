/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:07 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 18:50:47 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

void	open_inout_fds(t_exec *exec, t_elem_pars *elem)
{
	if (elem->args != NULL && elem->type == INFILE)
	{
		exec->infile = open(elem->args[0], O_RDONLY);
		if (exec->infile == -1)
		{
			write(2, "\n", 1);
			exit (0);
		}
	}
	if (elem->args != NULL && elem->type == OUTFILE)
	{
		exec->outfile = open(elem->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (exec->outfile == -1)
		{
			write(2, "\n", 1);
			close(exec->infile);
			exit (1);
		}
	}
}

void	init_exec_utils(t_exec *exec)
{
	exec->pid = 0;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
	exec->nbr_cmd = 0;
	exec->nbr_pipes = 0;
	exec->exit_code = 0;
	exec->status = 0;
	exec->cmds = NULL;
	exec->infile = INT_MIN;
	exec->outfile = INT_MIN;
	exec->pid = NULL;
}

t_exec	*init_exec_structure(t_exec *exec)
{
	t_elem_pars	*elem_lst;

	init_exec_utils(exec);
	elem_lst = g_data.parser_lst;
	if (elem_lst == NULL)
		return (NULL);
	while (elem_lst != NULL)
	{
		if (elem_lst->type == PIPE)
			exec->nbr_pipes++;
		if (elem_lst->type == COMMAND)
			exec->nbr_cmd++;
		if (elem_lst->next == NULL)
			break ;
		elem_lst = elem_lst->next;
	}
	return (exec);
}

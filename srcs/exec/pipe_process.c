/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:45:18 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 18:52:29 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

extern t_data	g_data;

void	parent_close(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
{
	close(exec->pipefd[1]);
	if (exec->infile >= 0)
		close(exec->infile);
	exec->infile = exec->pipefd[0];
}

void	child_process(t_elem_pars *start, t_elem_pars *elem_lst, t_exec *exec)
{
	child_open(start, elem_lst, exec);
	if (is_builtin(elem_lst->cmd))
	{
		builtin_process(exec, elem_lst);
		exit(0);
	}
	else
		exec_cmd(exec, start, elem_lst);
}

static void	pid_fail(void)
{
	perror("minishell: ");
	exit(1);
}

pid_t	fork_process(t_exec *exec)
{
	pid_t		pid;
	t_lst_pid	*new_pid_lst;
	t_lst_pid	*last_pid_lst;

	last_pid_lst = exec->pid;
	pid = fork();
	if (pid > 0)
	{
		new_pid_lst = garbage_alloc(&g_data.garb_lst, sizeof(t_lst_pid));
		if (!new_pid_lst)
			return (-1);
		new_pid_lst->pid = pid;
		new_pid_lst->next = NULL;
		if (exec->pid == NULL)
			exec->pid = new_pid_lst;
		else
		{
			while (last_pid_lst->next != NULL)
				last_pid_lst = last_pid_lst->next;
			last_pid_lst->next = new_pid_lst;
		}
	}
	return (pid);
}	

void	pipe_proc(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
{
	t_bool	has_cmd;

	has_cmd = false;
	while (elem != NULL)
	{
		has_cmd = is_cmd(has_cmd, elem);
		if (has_cmd && (elem->type == PIPE || !elem->next))
		{
			if (pipe(exec->pipefd) == -1)
				perror("minishell: ");
			exec->tmp_pid = fork_process(exec);
			if (exec->tmp_pid == -1)
				pid_fail();
			else if (exec->tmp_pid == 0)
				child_process(start, elem, exec);
			else
			{
				parent_close(start, elem, exec);
				if (elem->next)
					start = elem->next;
			}
			has_cmd = false;
		}
		elem = elem->next;
	}
}

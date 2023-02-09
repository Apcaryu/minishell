/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:45:18 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/09 13:45:44 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

// & PIPE
void	child_process(t_elem_pars *start, t_elem_pars *elem_lst, t_exec *exec)
{
	child_open(start, elem_lst, exec);
	dprintf(2, "\033[32melem.cmd = %s\033[0m\n", elem_lst->cmd);
	if (is_builtin(elem_lst->cmd))
	{
		dprintf(2, "\033[31melem.cmd = %s | arg[1] = %s\033[0m\n", \
			elem_lst->cmd, elem_lst->args[1]);
		builtin_process(exec, elem_lst);
		exit(0);
	}
	else
		exec_cmd(exec, start, elem_lst);
}

// & PIPE
void	pipe_proc(t_elem_pars *start, t_elem_pars *elem, t_exec *exec, int i)
{
	while (elem != NULL)
	{
		if (elem->type == PIPE || !elem->next)
		{
			dprintf(2, "\033[35melem.cmd = %s\033[0m\n", elem->cmd);
			if (pipe(exec->pipefd) == -1)
				perror("minishell: ");
			exec->pid = fork();
			if (exec->pid == -1)
			{
				perror("minishell: ");
				exit(1);
			}
			else if (exec->pid == 0)
				child_process(start, elem, exec);
			else
			{
				close(exec->pipefd[1]);
				if (exec->infile >= 0)
					close(exec->infile);
				exec->infile = exec->pipefd[0];
				if (elem->next)
					start = elem->next;
			}
			i++;
		}
		elem = elem->next;
	}
}

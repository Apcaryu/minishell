/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:45:18 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/10 15:33:31 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

void	parent_close(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
{
	close(exec->pipefd[1]);
	if (exec->infile >= 0)
		close(exec->infile);
	exec->infile = exec->pipefd[0];
}

// & PIPE
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

// & PIPE
void	pipe_proc(t_elem_pars *start, t_elem_pars *elem, t_exec *exec, int i)
{
	while (elem != NULL)
	{
		if (elem->type == PIPE || !elem->next)
		{
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
				parent_close(start, elem, exec);
				if (elem->next)
					start = elem->next;
			}
			i++;
		}
		elem = elem->next;
	}
}

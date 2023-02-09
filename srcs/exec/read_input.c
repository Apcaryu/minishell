/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/09 13:37:41 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

extern t_data	g_data;

// ^ KEEP
void	wait_loop(t_exec *exec)
{
	close(exec->pipefd[0]);
	close(exec->pipefd[1]);
	while (errno != ECHILD)
	{
		wait(&exec->pid);
		if (WIFEXITED(exec->status))
			exec->exit_code = WEXITSTATUS(exec->status);
	}
}

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
void	pipe_process(t_elem_pars *start, t_elem_pars *elem_lst, t_exec *exec, int i)
{
	while (elem_lst != NULL)
	{
		if (elem_lst->type == PIPE || !elem_lst->next)
		{
			dprintf(2, "\033[35melem.cmd = %s\033[0m\n", elem_lst->cmd);
			if (pipe(exec->pipefd) == -1)
				perror("minishell: ");
			exec->pid = fork();
			if (exec->pid == -1)
			{
				perror("minishell: ");
				exit(1);
			}
			else if (exec->pid == 0)
				child_process(start, elem_lst, exec);
			else
			{
				close(exec->pipefd[1]);
				if (exec->infile >= 0)
					close(exec->infile);
				exec->infile = exec->pipefd[0];
				if (elem_lst->next)
					start = elem_lst->next;
			}
			i++;
		}
		elem_lst = elem_lst->next;
	}
}

// ^ Keep
void	main_loop(t_exec *exec)
{
	int			i;
	t_elem_pars	*start;
	t_elem_pars	*elem_lst;
	int			stdin_cpy;
	int			stdout_cpy;

	i = 1;
	stdin_cpy = -1;
	stdout_cpy = -1;
	start = g_data.parser_lst;
	elem_lst = g_data.parser_lst;
	if (exec->nbr_pipes == 0 && check_all_builtin(elem_lst))
	{
		stdin_cpy = dup(0);
		stdout_cpy = dup(1);
		inout_before_proc(start, elem_lst, exec);
		builtin_process(exec, elem_lst);
		dup2(0, stdin_cpy);
		dup2(1, stdout_cpy);
	}
	else
		pipe_process(start, elem_lst, exec, i);
	if (exec->infile >= 0)
		close(exec->infile);
	wait_loop(exec);
}

// ^ Keep
void	executer(void)
{
	int		i;
	t_exec	*exec;

	i = 0;
	exec = garbage_alloc(&g_data.garb_lst, sizeof(t_exec));
	exec = init_exec_structure(exec);
	if (exec == NULL)
		return ;
	main_loop(exec);
	g_data.exec_struct = exec;
}

// ^ Keep
void	read_input(t_data *data)
{
	printf("input = %s\n", data->input);
	lexer();
	expend();
	parser();
	executer();
}

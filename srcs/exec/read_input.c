/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/09 12:36:27 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

extern t_data	g_data;

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

int	open_inout(t_elem_pars *elem, t_exec *exec)
{
	int	file;

	file = -1;
	if (elem->args != NULL && elem->type == INFILE)
	{
		file = open(elem->args[0], O_RDONLY, 0644);
		if (file == -1)
		{
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(0);
		}
	}
	else if (elem->args != NULL && elem->type == OUTFILE)
	{
		file = open(elem->args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file == -1)
		{
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(1);
		}
	}
	else if (elem->args != NULL && elem->type == APPEND)
	{
		file = open(elem->args[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (file == -1)
		{
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(1);
		}
	}
	else if (elem->args != NULL && elem->type == HEREDOC)
	{
		file = ft_heredoc(elem, exec);
	}
	return (file);
}

void	child_open(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
{
	char	*cmd;
	int		infile;
	int		outfile;

	infile = -2;
	outfile = -2;
	while ((elem->next != NULL && start != elem) \
		|| (elem->next == NULL && start != NULL))
	{
		if (start->type == INFILE)
			infile = open_inout(start, exec);
		else if (start->type == COMMAND)
			cmd = start->cmd;
		else if (start->type == OUTFILE)
			outfile = open_inout(start, exec);
		else if (start->type == APPEND)
			outfile = open_inout(start, exec);
		else if (start->type == HEREDOC)
		{
			infile = open_inout(start, exec);
		}
		start = start->next;
	}
	close(exec->pipefd[0]);
	if (infile >= 0)
	{
		dprintf(2, "fd:%d\n", infile);
		dup2(infile, 0);
		close(infile);
	}
	else if (exec->infile >= 0)
	{
		dup2(exec->infile, 0);
		close(exec->infile);
	}
	if (outfile >= 0)
	{
		dup2(outfile, 1);
		close(outfile);
	}	
	else if (elem->type == PIPE && outfile == -2)
		dup2(exec->pipefd[1], 1);
	if (exec->nbr_cmd == 0)
		exit (0);
	close(exec->pipefd[1]);
}

void	inout_before_proc(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
{
	char	*cmd;
	int		infile;
	int		outfile;

	infile = -2;
	outfile = -2;
	while ((elem->next != NULL && start != elem) \
		|| (elem->next == NULL && start != NULL))
	{
		if (start->type == INFILE)
			infile = open_inout(start, exec);
		else if (start->type == COMMAND)
			cmd = start->cmd;
		else if (start->type == OUTFILE)
			outfile = open_inout(start, exec);
		else if (start->type == APPEND)
			outfile = open_inout(start, exec);
		else if (start->type == HEREDOC)
			infile = open_inout(start, exec);
		start = start->next;
	}
	if (infile >= 0)
	{
		dup2(infile, 0);
		close(infile);
	}
	if (outfile >= 0)
	{
		dup2(outfile, 1);
		close(outfile);
	}
}

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

void	read_input(t_data *data)
{
	printf("input = %s\n", data->input);
	lexer();
	expend();
	parser();
	executer();
}

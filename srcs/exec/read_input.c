/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/12 15:23:06 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

void	check_command(char *input)
{
	if (!ft_strncmp("echo", input, ft_strlen("echo")))
		echo_exec();
	else if (!ft_strncmp("cd", input, ft_strlen("cd")))
		cd_exec();
	else if (!ft_strncmp("pwd", input, ft_strlen("pwd")))
		pwd_exec();
	else if (!ft_strncmp("export", input, ft_strlen("export")))
		export_exec();
	else if (!ft_strncmp("unset", input, ft_strlen("unset")))
		unset_exec();
	else if (!ft_strncmp("env", input, ft_strlen("env")))
		env_exec();
	else if (!ft_strncmp("exit", input, ft_strlen("exit")))
		exit_exec();
}

void	print_elem_lst(t_elem_pars *lst) // TODO remove
{
	if (lst == NULL)
		return;
//	while (lst->next != NULL) {
//		printf("elem = %p | type = %d | cmd = %s | arg = %s | next %p\n", lst, lst->type, lst->cmd, lst->args[0], lst->next);
//		lst = lst->next;
//	}
	printf("elem = %p | type = %d | cmd = %s | arg = %s | next %p\n", lst, lst->type, lst->cmd, lst->args[0], lst->next);
	lst = lst->next;
	printf("elem = %p | type = %d | cmd = %s | next %p\n", lst, lst->type, lst->cmd, lst->next);
	lst = lst->next;
	printf("elem = %p | type = %d | cmd = %s | next %p\n", lst, lst->type, lst->cmd, lst->next);
	lst = lst->next;
	printf("elem = %p | type = %d | cmd = %s | next %p\n", lst, lst->type, lst->cmd, lst->next);
	lst = lst->next;
	printf("elem = %p | type = %d | cmd = %s | arg = %s | next %p\n", lst, lst->type, lst->cmd, lst->args[0], lst->next);
}

void	print_exec_struct(t_exec *exec) // TODO remove
{
	if (exec == NULL)
		return;
	printf("exec structure = %p | pid[0] = %d | pid[1] = %d | pipefd[0] = %d | pipefd[1] = %d\n", exec, exec->pid[0], exec->pid[1], exec->pipefd[0], exec->pipefd[1]);
}

void	close_fd(t_exec *exec)
{
	int i;

	i = 0;
	// printf("exec->pid[%d] : %d\n", i, exec->pid[i]);
	while (i < 11)
	{
		// printf("exec->pid[%d] : %d\n", i, exec->pid[i]);
		if (exec->pid[i] >= 0)
		{
			close(exec->pid[i]);
		}
		i++;
	}
	close(exec->pipefd[0]);
	close(exec->pipefd[1]);
	close(exec->infile);
}

void	pipe_process(t_exec *exec)
{
	if (pipe(exec->pipefd) == -1)
	{
		perror("pipe: ");
		close(exec->pipefd[0]);
		close(exec->pipefd[1]);
	}
}

void	child_process(t_exec *exec, t_elem_pars *elem)
{
	close(exec->pipefd[0]);
	if (elem->type == INFILE)
	{
		printf("INFILE = %d\n", exec->infile);
		exec->exit_code = dup2(exec->infile, STDIN_FILENO);
		if (exec->exit_code == -1)
			perror("dup2: ");
		printf("infile->exit_code = %d\n", exec->exit_code);
		close(exec->infile);
	}
	if (elem->type == OUTFILE)
	{
		printf("OUTFILE = %d\n", exec->outfile);
		exec->exit_code = dup2(exec->outfile, STDOUT_FILENO);
		if (exec->exit_code == -1)
			perror("dup2: ");
		printf("outfile->exit_code = %d\n", exec->exit_code);
		close(exec->outfile);
	}
	else
	{
		printf("AUTRE pipefd[1] = %d\n", exec->pipefd[1]);
		exec->exit_code = dup2(exec->pipefd[1], STDOUT_FILENO);
		printf("pipefd[1]->exit_code = %d\n", exec->exit_code);
		if (exec->exit_code == -1)
			perror("dup2: ");
	}
	// printf("elem->type = %d\n", elem->type);
	close(exec->pipefd[1]);
}

int exiteur(int exit_code, t_exec *exec)
{
	close(exec->pid[0]);
	close(exec->pid[1]);
	// ft_lstclear(&g_data.garb_lst, &free);
	// exit(exit_code);
	return (exit_code);
}


int	wait_loop_bis(t_exec *exec)
{
	pid_t wait;
	
	close(exec->pipefd[1]);
	close(exec->pipefd[0]);
	wait = 0;
	exec->status = 0;
	while (wait != -1)
	{
		wait = waitpid(-1, &exec->status, 0);
		if (wait == *exec->pid)
			exec->status = exec->exit_code;
		continue ;
	}
	if (WIFEXITED(exec->status))
		exec->exit_code = WEXITSTATUS(exec->status);
	else
		exec->exit_code = exec->status;
	// return (exec->exit_code);
	return (exiteur(exec->exit_code, exec));
}

void	fork_cmds(t_exec *exec, int i)
{
	exec->pid[i] = fork();
}

void exec_cmd(t_exec *exec, t_elem_pars *elem)
{
	int access_out;
	
	access_out = -1;
	printf("ici\n");
	// printf("*exec->cmds = %s\n", *exec->cmds);
	if (elem->cmd != NULL)
		access_out = access(elem->cmd, F_OK);
	if (access_out == 0)
		execve(elem->cmd, &elem->cmd, g_data.env); 
}

int	main_loop(t_exec *exec)
{
	int i;
	t_elem_pars	*elem_pars;
	t_bool is_fork = false;

	i = 1;
	elem_pars = g_data.parser_lst;
	// printf("type : %d | next : %p\n", g_data.parser_lst->type, g_data.parser_lst->next);
	while (elem_pars->next != NULL)
	{
		open_inout_fds(exec);
		pipe_process(exec);
		if (!is_fork)
		{
			is_fork = true;
			exec->pid[i] = fork();
		}
		if (elem_pars->type == PIPE)
			is_fork = false;
	// 	fork_cmds(exec, i);
	// 	// printf("exec->pid[%d] : %d\n", i, exec->pid[i]);
		if (exec->pid[i] == -1)
		{
			perror("minishell: ");
			exit (1);
		}
		else if (exec->pid[i] == 0)
		{
			// printf("exec->pid[%d] : %d\n", i, exec->pid[i]);
			child_process(exec, elem_pars);
			exec_cmd(exec, elem_pars);
		}
		else
		{
			close(exec->pipefd[1]);
			close(exec->infile);
			exec->infile = exec->pipefd[0];
		}
	// 	// printf("pid = %d\n", exec->pid[i]);
	// 	// printf("pipefd[0] : %d\n", exec->pipefd[0]);
	// 	// printf("pipefd[1] : %d\n", exec->pipefd[1]);
		close_fd(exec);
		i+=1;
		elem_pars = elem_pars->next;
	}
	// printf("i = %d\n", i);
	// // wait_loop(exec);
	return (wait_loop_bis(exec));
}

void	executer(void)
{
	// t_token *lex_lst;
	t_exec	*exec;
	int		i;

	i = 0;
	exec = garbage_alloc(&g_data.garb_lst, sizeof(t_exec));
	init_test_exec();
	printf("input = < in cat | ls > out\n");
	// print_elem_lst(g_data.parser_lst);
	// init_open_fd(); // TODO
	exec = init_exec_structure(exec); // TODO
	// print_exec_struct(g_data.exec_struct);
	// print_exec_struct(exec);
	if (!main_loop(exec)) // TODO
		return ;
}

void	read_input(t_data *data)
{
//	printf("input = %s\n", data->input);
	// lexer(data);
	// parser();
	executer();
	
//	check_command(input);
}
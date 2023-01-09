/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/09 18:57:29 by meshahrv         ###   ########.fr       */
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
	while (i < exec->nbr_pipes)
	{
		if (exec->pid[i] >= 0)
			close(exec->pid[i]);
		i++;
	}
	close(exec->pipefd[0]);
	close(exec->pipefd[1]);
}

void	pipe_process(t_exec *exec)
{
	int i;

	i = 0;
	while (i < exec->nbr_pipes)
	{
		if (pipe(exec->pipefd) == -1)
		{
			perror("pipe: ");
			close(exec->pipefd[0]);
			close(exec->pipefd[1]);
		}
		printf("pipefd[0] : %d\n", exec->pipefd[0]);
		printf("pipefd[1] : %d\n", exec->pipefd[1]);
		
		i++;
	}
}

// int	child_exec(t_exec *exec, t_data *data, int invalid)
// {
// 	char	*cmd;
// 	int		fork_nbr;
	
// 	fork_nbr = 0;
// 	exec->pid[fork_nbr] = fork();
// 	if (exec->pid[fork_nbr] == -1)
// 	{
// 		perror("minishell: ");
// 		exit (1);
// 	}
// 	if (exec->pid[fork_nbr] == 0)
// 	{
		
// 	}
// 	return (fork_nbr ++, 0);
// }

// void	exec_process()
// {
	
// }

void	wait_loop(t_exec *exec)
{
	int wait;
	int	j;
	t_elem_pars	*elem_pars;

	elem_pars = g_data.parser_lst;
	j = -1;
	close(exec->pipefd[1]);
	close(exec->pipefd[0]);
	while (elem_pars->next != NULL && j < 2)
	{
		wait = waitpid(exec->pid[j], &exec->status, 0);
		// printf("wait : %d\n", wait);
		if (WIFEXITED(exec->status))
			exec->exit_code = WEXITSTATUS(exec->status);
		j++;
		elem_pars = elem_pars->next;
	}
	exit (exec->exit_code);
}

void	main_loop(t_exec *exec)
{
	int i;
	t_elem_pars	*elem_pars;

	i = 1;
	elem_pars = g_data.parser_lst;
	// printf("type : %d | next : %p\n", g_data.parser_lst->type, g_data.parser_lst->next);
	while (elem_pars->next != NULL)
	{
		pipe_process(exec);
		exec->pid[i] = fork();
		if (exec->pid[i] == -1)
		{
			perror("minishell: ");
			exit (1);
		}
		else if (exec->pid[i] == 0)
		{
			// child_process(exec);
			close_fd(exec);
		}
		printf("pid = %d\n", exec->pid[i]);
		printf("pipefd[0] : %d\n", exec->pipefd[0]);
		printf("pipefd[1] : %d\n", exec->pipefd[1]);
		i++;
		elem_pars = elem_pars->next;
	}
	wait_loop(exec);
	// waitpid(-1, NULL, 0);
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
	main_loop(exec); // TODO
}

void	read_input(t_data *data)
{
//	printf("input = %s\n", data->input);
	// lexer(data);
	// parser();
	executer();
//	check_command(input);
}
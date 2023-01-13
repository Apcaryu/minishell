/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/13 18:52:06 by meshahrv         ###   ########.fr       */
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
	printf("exec structure = %p | pid = %d | pipefd[0] = %d | pipefd[1] = %d\n", exec, exec->pid, exec->pipefd[0], exec->pipefd[1]);
}

void	close_fd(t_exec *exec)
{
	close(exec->pipefd[0]);
	close(exec->pipefd[1]);
	close(exec->infile);
}

void	pipe_process(t_exec *exec)
{
	if (0 < exec->nbr_pipes)
	{
		exec->nbr_pipes -= 1;
		if (pipe(exec->pipefd) == -1)
		{
			perror("pipe: ");
			close(exec->pipefd[0]);
			close(exec->pipefd[1]);
		}
	}
}

void	child_process(t_exec *exec, t_elem_pars *elem)
{
	dprintf(2,"type of elem = %d\n", elem->next->type);
	close(exec->pipefd[0]);
	if (elem->type == INFILE)
	{
		printf("INFILE = %d\n", exec->infile);
		exec->exit_code = dup2(exec->infile, STDIN_FILENO);
		if (exec->exit_code == -1)
			perror("dup2: ");
		dprintf(2,"infile->exit_code = %d\n", exec->exit_code);
		close(exec->infile);
	}
	if (elem->next->type == OUTFILE)
	{
		printf("OUTFILE = %d\n", exec->outfile);
		exec->exit_code = dup2(exec->outfile, STDOUT_FILENO);
		if (exec->exit_code == -1)
			perror("dup2: ");
		dprintf(2,"outfile->exit_code = %d\n", exec->exit_code);
		close(exec->outfile);
	}
	else
	{
		printf("AUTRE pipefd[1] = %d\n", exec->pipefd[1]);
		exec->exit_code = dup2(exec->pipefd[1], STDOUT_FILENO);
		dprintf(2, "pipefd[1]->exit_code = %d\n", exec->exit_code);
		if (exec->exit_code == -1)
			perror("dup2: ");
	}
	// printf("elem->type = %d\n", elem->type);
	close(exec->pipefd[1]);
}

int exiteur(int exit_code, t_exec *exec)
{
	close(exec->pid);
	// ft_lstclear(&g_data.garb_lst, &free);
	// exit(exit_code);
	return (exit_code);
}


// int	wait_loop_bis(t_exec *exec)
// {
// 	pid_t wait;
	
// 	close(exec->pipefd[1]);
// 	close(exec->pipefd[0]);
// 	wait = 0;
// 	exec->status = 0;
// 	while (wait != -1)
// 	{
// 		wait = waitpid(-1, &exec->status, 0);
// 		if (wait == exec->pid)
// 			exec->status = exec->exit_code;
// 		continue ;
// 	}
// 	if (WIFEXITED(exec->status))
// 		exec->exit_code = WEXITSTATUS(exec->status);
// 	else
// 		exec->exit_code = exec->status;
// 	// return (exec->exit_code);
// 	return (exiteur(exec->exit_code, exec));
// }

void	wait_loop_bis(t_exec *exec)
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

void	fork_cmds(t_exec *exec, int i)
{
	exec->pid = fork();
}

char	**get_env(t_exec *exec)
{
	int i;
	char	**tab;

	i = 0;
	while (ft_strnstr(g_data.env[i], "PATH", 4) == 0)
		i++;
	tab = ft_split(g_data.env[i] + 5, ':');
	return (tab);
}

void	exec_path(t_elem_pars *start, t_exec *exec)
{
	int		i;
	int		j;
	char	*tmp;
	char 	**tab;
	char	*path;
	
	i = 0;
	j = 0;
	tab = get_env(exec);
	while (tab[j])
	{
		// dprintf(2, "Path = %s\n", tab[i]);
		j++;
	}
	while (tab[i])
	{
		tmp = ft_strjoin(tab[i], "/");
		path = ft_strjoin(tmp, start->cmd);
		// dprintf(2, "start->cmd = %s\n", start->cmd);
		// dprintf(2, "tmp = %s | path = %s\n", tmp, path);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			exec->exit_code = execve(path, start->args, g_data.env);
		}
		free(path);
		i++;
	}
}

void exec_cmd(t_exec *exec, t_elem_pars *start, t_elem_pars *elem)
{
	int access_out;
	
	access_out = -1;
	while (((elem->next != NULL && start != elem) || (elem->next == NULL && start != NULL)) && start->type != COMMAND)
	{
		start = start->next;
	}
	// dprintf(2, "*exec->cmds = %s\n", *exec->cmds);
	// if (start->cmd != NULL)
	// 	access_out = access(start->cmd, F_OK);
	// if (access_out == 0)
	// 	execve("/bin/", elem->args, NULL /*g_data.env*/);
	if (start->type == COMMAND)
		exec_path(start, exec);
	// exit (127);
}

static int	open_inout(t_elem_pars *elem)
{
	int file;

	file = -1;
	// dprintf(2, "type = %d\n", elem->type);
	if (elem->args != NULL && elem->type == INFILE)
	{
		file = open(elem->args[0], O_RDONLY);
		if (file == -1)
		{
			// error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
		}
	}
	if (elem->args != NULL && elem->type == OUTFILE)
	{
		file = open(elem->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (file == -1)
		{
			// error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
		}
	}
	return (file);
}

void child(t_elem_pars *start, t_elem_pars *elem, t_exec *exec, int i)
{
	int infile;
	int outfile;
	char *cmd;

	infile = -2;
	outfile = -2;
	
	while ((elem->next != NULL && start != elem) || (elem->next == NULL && start != NULL)){
		if (start->type == INFILE)
			infile = open_inout(start);
		else if (start->type == COMMAND)
			cmd = start->cmd;
		else if (start->type == OUTFILE)
			outfile = open_inout(start);
		start = start->next;
	}
	close(exec->pipefd[0]);
	if (infile >= 0){
		dup2(infile, 0);
		close(infile);
	}

	if (outfile >= 0){
		dup2(outfile, 1);
		close(outfile);
	}
	else if (elem->type == PIPE && outfile == -2)
		dup2(exec->pipefd[1],1);
	close(exec->pipefd[1]);
	
	
}

void	main_loop_2(t_exec *exec)
{
	t_elem_pars	*start;
	int i = 1;
	t_elem_pars *elem_lst;
	
	start = g_data.parser_lst;
	elem_lst = g_data.parser_lst;
	while (elem_lst != NULL)
	{
		// open_inout_fds(exec, elem_lst);
		if (elem_lst->type == PIPE || !elem_lst->next)
		{
			pipe(exec->pipefd);
			exec->pid = fork();
			if (exec->pid == 0)
			{
				child(start, elem_lst, exec, i);
				exec_cmd(exec, start, elem_lst);
				exit(127);
			}
			else
			{
				close(exec->pipefd[1]);
				dup2(exec->pipefd[0], 0);
				close(exec->pipefd[0]);
				if (elem_lst->next)
					start = elem_lst->next;
			}
			i++;
		}
		elem_lst = elem_lst->next;
	}
	wait_loop_bis(exec);
	
}
/*
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
		open_inout_fds(exec, elem_pars);
		printf("infile = %d\n", exec->infile);
		pipe_process(exec);
		if (!is_fork)
		{
			is_fork = true;
			exec->pid[i] = fork();
		}
		if (elem_pars->type == PIPE)
			is_fork = false;
	// // 	fork_cmds(exec, i);
		// printf("exec->pid[%d] : %d\n", i, exec->pid[i]);
		if (exec->pid[i] == -1)
		{
			perror("minishell: ");
			exit (1);
		}
		else if (exec->pid[i] == 0)
		{
			// printf("exec->pid[%d] : %d\n", i, exec->pid[i]);
			child_process(exec, elem_pars);
			if (elem_pars->type == COMMAND)
				exec_cmd(exec, elem_pars);
		}
	// 	else
	// 	{
	// 		close(exec->pipefd[1]);
	// 		close(exec->infile);
	// 		exec->infile = exec->pipefd[0];
	// 	}
		// close_fd(exec);
		i+=2;
		elem_pars = elem_pars->next;
		
	}
	if (elem_pars->next == NULL)
	{
		open_inout_fds(exec, elem_pars);
		printf("outfile = %d\n", exec->outfile);
		if (exec->pid[i] == 0)
		{
			// printf("exec->pid[%d] : %d\n", i, exec->pid[i]);
			child_process(exec, elem_pars);
			// exec_cmd(exec, elem_pars);
			if (elem_pars->type == COMMAND)
				exec_cmd(exec, elem_pars);
		}
	}
	// printf("i = %d\n", i);
	// // wait_loop(exec);
	return (wait_loop_bis(exec));
}*/

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
	main_loop_2(exec);
	// if (!main_loop_2(exec)) // TODO
	// 	return ;
}

void	read_input(t_data *data)
{
//	printf("input = %s\n", data->input);
	// lexer(data);
	// parser();
	executer();
	
//	check_command(input);
}
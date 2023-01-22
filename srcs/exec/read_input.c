/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/20 18:01:32 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

// void	check_builtin()
// {
// 	if (!ft_strncmp("echo", input, ft_strlen("echo")))
// 		echo_exec();
// 	else if (!ft_strncmp("cd", input, ft_strlen("cd")))
// 		cd_exec();
// 	else if (!ft_strncmp("pwd", input, ft_strlen("pwd")))
// 		pwd_exec();
// 	else if (!ft_strncmp("export", input, ft_strlen("export")))
// 		export_exec();
// 	else if (!ft_strncmp("unset", input, ft_strlen("unset")))
// 		unset_exec();
// 	else if (!ft_strncmp("env", input, ft_strlen("env")))
// 		env_exec();
// 	else if (!ft_strncmp("exit", input, ft_strlen("exit")))
// 		exit_exec();
// }

t_bool    is_builtin(char *cmd)
{
    if (!cmd)
        return (false);
    if (ft_strncmp("echo", cmd, ft_strlen("echo")) == 0 || ft_strncmp("env", cmd, ft_strlen("env")) == 0 \
    || ft_strncmp("export", cmd, ft_strlen("export")) == 0 || ft_strncmp("pwd", cmd, ft_strlen("pwd")) == 0 \
    || ft_strncmp("exit", cmd, ft_strlen("exit")) == 0 || ft_strncmp("cd", cmd, ft_strlen("cd")) == 0 \
    || ft_strncmp("unset", cmd, ft_strlen("unset")) == 0)
        return (true);
    return (false);
}

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
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(0);
		}
	}
	if (elem->args != NULL && elem->type == OUTFILE)
	{
		file = open(elem->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (file == -1)
		{
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(1);
		}
	}
	return (file);
}

void child(t_elem_pars *start, t_elem_pars *elem, t_exec *exec, int i)
{
	char	*cmd;
	int		infile;
	int		outfile;

	infile = -2;
	outfile = -2;
	while ((elem->next != NULL && start != elem) || (elem->next == NULL && start != NULL))
	{
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
	else if (exec->infile >= 0){
		dup2(exec->infile, 0);
		close(exec->infile);
	}
	
	if (outfile >= 0){
		dup2(outfile, 1);
		close(outfile);
	}
	else if (elem->type == PIPE && outfile == -2)
		dup2(exec->pipefd[1],1);
	close(exec->pipefd[1]);
}

void	builtin_process(t_exec *exec)
{
	int i;

	if (!ft_strncmp("echo", g_data.parser_lst->cmd, ft_strlen("echo")))
		echo_exec();
	else if (!ft_strncmp("env", g_data.parser_lst->cmd, ft_strlen("env")))
		env_exec();
	else if (!ft_strncmp("pwd", g_data.parser_lst->cmd, ft_strlen("pwd")))
		pwd_exec();
	else if (!ft_strncmp("cd", g_data.parser_lst->cmd, ft_strlen("cd")))
		cd_exec();

	else if (!ft_strncmp("exit", g_data.parser_lst->cmd, ft_strlen("exit")))
		exit_exec(exec);
	else if (!ft_strncmp("export", g_data.parser_lst->cmd, ft_strlen("export")))
	{
		i = 0;
		while (g_data.parser_lst->args[++i])
		{
			export_exec(g_data.parser_lst->args[i]);
		}
		// export_exec();
	}
}

void	main_loop(t_exec *exec)
{
	int			i;
	t_elem_pars	*start;
	t_elem_pars	*elem_lst;
	
	i = 1;
	start = g_data.parser_lst;
	elem_lst = g_data.parser_lst;
	dprintf(2, "ARGS == %s\n", g_data.parser_lst->cmd);
	// if (is_builtin(g_data.parser_lst->cmd))
    // {
    //     // dprintf(2, "hello\n");
    //     builtin_process(exec);
    // }
	// else
	// {
		while (elem_lst != NULL)
		{
			if (elem_lst->type == PIPE || !elem_lst->next)
			{
				// pipe(exec->pipefd);
				if (pipe(exec->pipefd) == -1)
					perror("minishell: ");
				exec->pid = fork();
				if (exec->pid == -1)
				{
					perror("minishell: ");
					exit(1);
				}
				else if (exec->pid == 0)
				{
					child(start, elem_lst, exec, i);
					if (is_builtin(elem_lst->cmd))
    				{
        				// dprintf(2, "hello\n");
        				builtin_process(exec);
						exit(0);
    				}
					else
						exec_cmd(exec, start, elem_lst);
					// exit(127);
				}
				else
				{
					close(exec->pipefd[1]);
					// dup2(exec->pipefd[0], 0);
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
	// }
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
//	printf("input = < in cat | ls > out\n");
	exec = init_exec_structure(exec);
	if (exec == NULL)
		return ;
	main_loop(exec);
	g_data.exec_struct = exec;
}

void	read_input(t_data *data)
{
	printf("input = %s\n", data->input);
	//n_lexer();
	//expend();
	lexer();
	expend();
	parser();
//	check_command(input);

	// lexer(data);
	// parser();
//	init_test_exec();
	executer();
	//dprintf(2, "cmd = %s\n", g_data.parser_lst->args[0]);
//	 check_builtin();
//	if (!ft_strncmp("echo", g_data.parser_lst->args[0], ft_strlen("echo")))
//		echo_exec();
//	else if (!ft_strncmp("env", g_data.parser_lst->args[0], ft_strlen("env")))
//		env_exec();
//	else if (!ft_strncmp("pwd", g_data.parser_lst->args[0], ft_strlen("pwd")))
//		pwd_exec();
//	else if (!ft_strncmp("exit", g_data.parser_lst->args[0], ft_strlen("exit")))
//		exit_exec();
//	else if (!ft_strncmp("cd", g_data.parser_lst->args[0], ft_strlen("cd")))
//		cd_exec();
}
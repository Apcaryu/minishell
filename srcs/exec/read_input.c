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

void	init_test_exec()
{
	t_elem_pars *element;

	/*for: < in cat | ls > out*/

	element = NULL;

	g_data.parser_lst = NULL;
	element = new_elem_pars(&g_data.garb_lst);
	element->type = INFILE;
	element->cmd = NULL;
	element->args = garbage_alloc(&g_data.garb_lst, 1 * sizeof(char *));
	element->args[0] = "in";
	elem_pars_add_back(&g_data.parser_lst, element);

	element = new_elem_pars(&g_data.garb_lst);
	element->type = COMMAND;
	element->cmd = "cat";
	element->args = NULL;
	elem_pars_add_back(&g_data.parser_lst, element);

	element = new_elem_pars(&g_data.garb_lst);
	element->type = PIPE;
	element->cmd = NULL;
	element->args = NULL;
	elem_pars_add_back(&g_data.parser_lst, element);

	element = new_elem_pars(&g_data.garb_lst);
	element->type = COMMAND;
	element->cmd = "ls";
	element->args = NULL;
	elem_pars_add_back(&g_data.parser_lst, element);

	element = new_elem_pars(&g_data.garb_lst);
	element->type = OUTFILE;
	element->cmd = NULL;
	element->args = garbage_alloc(&g_data.garb_lst, 1 * sizeof(char *));
	element->args[0] = "out";
	elem_pars_add_back(&g_data.parser_lst, element);

}

// void	init_structure()
// {
// 	t_exec	exec;

// 	exec.infile = open(av[1], O_RDONLY);
// 	if (exec.infile == -1)
// 	{
// 		error_msgs(av[1], strerror(errno));
// 		write(2, "\n", 1);
// 		exit (0);
// 	}
// 	exec.outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (exec.outfile == -1)
// 	{
// 		error_msgs(av[4], strerror(errno));
// 		write(2, "\n", 1);
// 		close(exec.infile);
// 		exit (1);
// 	}
// 	exec.pipefd[0] = -1;
// 	exec.pipefd[1] = -1;
// 	exec.argc = ac;
// 	exec.av = av;
// 	exec.path = NULL;
// 	exec.env = en
// 	exec.exit_code = 0;
// 	exec.index_main = 1;
// 	exec.status = 0;
// 	exec.pid[0] = INT_MIN;
// 	exec.pid[1] = INT_MIN;
// 	exec.cmd = NULL;
// }

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

void	print_exec_struct(t_exec *exec)
{
	if (exec == NULL)
		return;
	printf("exec structure = %p | pid[0] = %d | pid[1] = %d | pipefd[0] = %d | pipefd[1] = %d\n", exec, exec->pid[0], exec->pid[1], exec->pipefd[0], exec->pipefd[1]);
}

t_exec	*init_exec_structure()
{
	t_exec *exec;

	exec->pid[0] = INT_MIN;
	exec->pid[1] = INT_MIN;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
	exec->nbr_cmd = 0;
	exec->nbr_pipes = 0;
	exec->exit_code = 0;
	exec->status = 0;
	while (g_data.parser_lst->next != NULL)
	{
		if (g_data.parser_lst->type == PIPE)
		{
			exec->nbr_pipes++;
			printf("pipes = %d\n", exec->nbr_pipes);
		}
		if (g_data.parser_lst->type == COMMAND)
		{
			exec->nbr_cmd++;
			printf("cmds = %d\n", exec->nbr_cmd);
		}
		g_data.parser_lst = g_data.parser_lst->next;
	}
	// printf("exec structure = %p | pid[0] = %d | pid[1] = %d | pipefd[0] = %d | pipefd[1] = %d\n", exec, exec->pid[0], exec->pid[1], exec->pipefd[0], exec->pipefd[1]);
	return (exec);
}

void	child_process()
{

}

void	main_loop(t_exec *exec)
{
	// int	i;

	// i = 0;
	// while (g_data.parser_lst->next != NULL)
	// {
		if (pipe(exec->pipefd) == -1)
			perror("minishell: ");
		*exec->pid = fork();
		if (*exec->pid == -1)
		{
			perror("minishell: ");
			exit (1);
		}
		// else if (*exec->pid == 0)
		// 	child_process();		
		printf("pid = %d\n", *exec->pid);
		// i++;
		waitpid(-1, NULL, 0);
		// g_data.parser_lst = g_data.parser_lst->next;
	// }
}

void	executer(void)
{
	// t_token *lex_lst;
	t_exec	*exec;
	int		i;

	i = 0;
	init_test_exec();
	printf("input = < in cat | ls > out\n");
	print_elem_lst(g_data.parser_lst);
	// init_open_fd(); // TODO
	exec = init_exec_structure(); // TODO
	// print_exec_struct(g_data.exec_struct);
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
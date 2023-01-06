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

	g_data.parser_lst = NULL;
	element = new_elem_pars(g_data.garb_lst);
	element->type = INFILE;
	element->cmd = NULL;
	element->args[0] = "in";
	elem_pars_add_back(g_data.parser_lst, element);

	element = new_elem_pars(g_data.garb_lst);
	element->type = COMMAND;
	element->cmd = "cat";
	element->args = NULL;
	elem_pars_add_back(g_data.parser_lst, element);

	element = new_elem_pars(g_data.garb_lst);
	element->type = PIPE;
	element->cmd = NULL;
	element->args = NULL;
	elem_pars_add_back(g_data.parser_lst, element);

	element = new_elem_pars(g_data.garb_lst);
	element->type = COMMAND;
	element->cmd = "ls";
	element->args = NULL;
	elem_pars_add_back(g_data.parser_lst, element);

	element = new_elem_pars(g_data.garb_lst);
	element->type = OUTFILE;
	element->cmd = NULL;
	element->args[0] = "out";
	elem_pars_add_back(g_data.parser_lst, element);
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

void	executer(void)
{
	// t_token *lex_lst;
	t_exec	*exec;
	int		i;

	i = 0;
	g_data.exec_lst = garbage_alloc(&g_data.garb_lst, sizeof(t_exec));
	init_test_exec();
	// while (g_data.input[i] == ' ')
		// 	i++;
		// exec = new_exec(&g_data.garb_lst);
		// printf("cmd = %s | args = %p | idx = %d\n | next = %p\n", exec->cmd, exec->args, i, exec->next);
		// exec_add_back(&g_data.exec_lst, exec);
}

void	read_input(t_data *data)
{
	printf("hello\n");
	printf("input = %s\n", data->input);
	// lexer(data);
	// parser();
	executer();
//	check_command(input);
}
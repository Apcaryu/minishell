/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:07 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/11 20:08:31 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

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

void	open_inout_fds(t_exec *exec)
{
	if (g_data.parser_lst->args != NULL && g_data.parser_lst->type == INFILE)
	{
		exec->infile = open(g_data.parser_lst->args[0], O_RDONLY);
		if (exec->infile == -1)
		{
			// error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit (0);
		}
	}
	if (g_data.parser_lst->args != NULL && g_data.parser_lst->type == OUTFILE)
	{
		exec->outfile = open(g_data.parser_lst->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (exec->outfile == -1)
		{
			// error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			close(exec->infile);
			exit (1);
		}
	}
}

t_exec	*init_exec_structure(t_exec *exec)
{
	t_elem_pars *elem_lst;
	
	exec->pid[0] = 0;
	exec->pid[1] = 0;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
	exec->nbr_cmd = 0;
	exec->nbr_pipes = 0;
	exec->exit_code = 0;
	exec->status = 0;
	exec->cmds = NULL;
	
	elem_lst = g_data.parser_lst;
	while (elem_lst->next != NULL)
	{
		if (elem_lst->type == PIPE)
		{
			exec->nbr_pipes++;
			printf("pipes = %d\n", exec->nbr_pipes);
		}
		if (elem_lst->type == COMMAND)
		{
			exec->nbr_cmd++;
			printf("cmds = %d\n", exec->nbr_cmd);
		}
		if (elem_lst->next == NULL)
			break;
		elem_lst = elem_lst->next;
	}
	// printf("exec structure = %p | pid[0] = %d | pid[1] = %d | pipefd[0] = %d | pipefd[1] = %d\n", exec, exec->pid[0], exec->pid[1], exec->pipefd[0], exec->pipefd[1]);
	return (exec);
}
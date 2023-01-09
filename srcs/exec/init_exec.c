/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:07 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/09 13:57:51 by meshahrv         ###   ########.fr       */
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

t_exec	*init_exec_structure(t_exec *exec)
{
	exec->pid[0] = INT_MIN;
	exec->pid[1] = INT_MIN;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
	exec->nbr_cmd = 0;
	exec->nbr_pipes = 0;
	exec->exit_code = 0;
	exec->status = 0;
	exec->cmds = NULL;
	
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
		if (g_data.parser_lst->next == NULL)
			break;
		g_data.parser_lst = g_data.parser_lst->next;
	}
	// printf("exec structure = %p | pid[0] = %d | pid[1] = %d | pipefd[0] = %d | pipefd[1] = %d\n", exec, exec->pid[0], exec->pid[1], exec->pipefd[0], exec->pipefd[1]);
	return (exec);
}
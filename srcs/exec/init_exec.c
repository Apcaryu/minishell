/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:07 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/08 17:02:31 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

// void	init_test_exec()
// {
// 	t_elem_pars *element;

// 	/*for: < in cat | ls | rev > out*/
	
// 	element = NULL;

// 	// g_data.parser_lst = NULL;
// 	// element = new_elem_pars(&g_data.garb_lst);
// 	// element->type = INFILE;
// 	// element->cmd = NULL;
// 	// element->args = garbage_alloc(&g_data.garb_lst, 1 * sizeof(char *));
// 	// element->args[0] = "in";
// 	// elem_pars_add_back(&g_data.parser_lst, element);

// 	element = new_elem_pars(&g_data.garb_lst);
// 	element->type = COMMAND;
// 	element->cmd = "echo";
// 	element->args = garbage_alloc(&g_data.garb_lst, 5 * sizeof(char *));
// 	element->args[0] = "echo";
// 	element->args[1] = "-nnnnnnnn";
// 	element->args[2] = "nyuthvgbyugb";
// 	element->args[3] = "-nnnnnnnn";
// 	element->args[4] = NULL;
// 	elem_pars_add_back(&g_data.parser_lst, element);
	
// 	// element = new_elem_pars(&g_data.garb_lst);
// 	// element->type = PIPE;
// 	// element->cmd = NULL;
// 	// element->args = NULL;
// 	// elem_pars_add_back(&g_data.parser_lst, element);

// 	// g_data.parser_lst = NULL;
// 	// element = new_elem_pars(&g_data.garb_lst);
// 	// element->type = INFILE;
// 	// element->cmd = NULL;
// 	// element->args = garbage_alloc(&g_data.garb_lst, 1 * sizeof(char *));
// 	// element->args[0] = "in2";
// 	// elem_pars_add_back(&g_data.parser_lst, element);

// 	// element = new_elem_pars(&g_data.garb_lst);
// 	// element->type = COMMAND;
// 	// element->cmd = "rev";
// 	// element->args = garbage_alloc(&g_data.garb_lst, 2 * sizeof(char *));
// 	// element->args[0] = "rev";
// 	// element->args[1] = NULL;
// 	// elem_pars_add_back(&g_data.parser_lst, element);

// 	// element = new_elem_pars(&g_data.garb_lst);
// 	// element->type = PIPE;
// 	// element->cmd = NULL;
// 	// element->args = NULL;
// 	// elem_pars_add_back(&g_data.parser_lst, element);

// 	// element = new_elem_pars(&g_data.garb_lst);
// 	// element->type = COMMAND;
// 	// element->cmd = "rev";
// 	// element->args = garbage_alloc(&g_data.garb_lst, 2 * sizeof(char *));
// 	// element->args[0] = "rev";
// 	// element->args[1] = NULL;
// 	// elem_pars_add_back(&g_data.parser_lst, element);

// 	// element = new_elem_pars(&g_data.garb_lst);
// 	// element->type = OUTFILE;
// 	// element->cmd = NULL;
// 	// element->args = garbage_alloc(&g_data.garb_lst, 1 * sizeof(char *));
// 	// element->args[0] = "out";
// 	// elem_pars_add_back(&g_data.parser_lst, element);
// }

void	open_inout_fds(t_exec *exec, t_elem_pars *elem)
{
	// dprintf(2, "type = %d\n", elem->type);
	if (elem->args != NULL && elem->type == INFILE)
	{
		exec->infile = open(elem->args[0], O_RDONLY);
		if (exec->infile == -1)
		{
			// error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit (0);
		}
	}
	if (elem->args != NULL && elem->type == OUTFILE)
	{
		exec->outfile = open(elem->args[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (exec->outfile == -1)
		{
			// error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			close(exec->infile);
			exit (1);
		}
	}
}

void count_process(int nbr_pipe, t_elem_pars *elem)
{
	int nbr_process;
	t_elem_pars *tmp;
	t_bool *tab;
	int idx;

	tmp = elem;
	idx = 0;
	nbr_process = nbr_pipe + 1;
	dprintf(2, "nbr_process = %d\n", nbr_process);
	tab = malloc(sizeof(t_bool) * nbr_process);
	if (tab == NULL)
		return ;
	while (idx < nbr_process)
	{
		tab[idx] = false;
		idx++;
	}
	idx = 0;
	if (tmp->next == NULL)
	{
		if (tmp->type == COMMAND)
		{
			tab[idx] = true;
			dprintf(2, "tab[0] = %d\n", tab[0]);
			return ;	
		}
	}
	while (tmp->next != NULL)
	{
		if (tmp->type == COMMAND)
			tab[idx] = true;
		if (tmp->type == PIPE)
			idx++;
		tmp = tmp->next;
		if (tmp->next == NULL)
		{
			if (tmp->type == COMMAND)
			{
				tab[idx] = true;
				break ;
			}
		}
	}
	idx = 0;
	while (idx < nbr_process)
	{
		dprintf(2, "tab[%d] = %d\n", idx, tab[idx]);
		idx++;
	}
}

t_exec	*init_exec_structure(t_exec *exec)
{
	t_elem_pars *elem_lst;
	
	exec->pid = 0;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
	exec->nbr_cmd = 0;
	exec->nbr_pipes = 0;
	exec->exit_code = 0;
	exec->status = 0;
	exec->cmds = NULL;
	exec->infile = INT_MIN;
	exec->outfile = INT_MIN;
	
	
	elem_lst = g_data.parser_lst;
	if (elem_lst == NULL)
		return (NULL);
	while (elem_lst != NULL)
	{
		if (elem_lst->type == PIPE)
		{
			exec->nbr_pipes++;
			dprintf(2, "pipes = %d\n", exec->nbr_pipes);
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
	// printf("exec structure = %p | pid = %d | pid[1] = %d | pipefd[0] = %d | pipefd[1] = %d\n", exec, exec->pid, exec->pid[1], exec->pipefd[0], exec->pipefd[1]);
	// count_process(exec->nbr_pipes, g_data.parser_lst);
	return (exec);
}

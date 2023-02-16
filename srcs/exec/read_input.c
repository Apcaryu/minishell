/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:50:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 13:01:46 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"
#include "../../headers/error_msg.h"

extern t_data	g_data;

void	dup_close_zero(t_exec *exec)
{
	dup2(exec->stdsave[0], 0);
	close(exec->stdsave[0]);
}

void	dup_close_one(t_exec *exec)
{
	dup2(exec->stdsave[1], 1);
	close(exec->stdsave[1]);
}

void	main_loop(t_exec *exec)
{
	int			i;
	t_elem_pars	*start;
	t_elem_pars	*elem_lst;

	i = 1;
	start = g_data.parser_lst;
	elem_lst = g_data.parser_lst;
	if (exec->nbr_pipes == 0 && check_all_builtin(elem_lst))
	{
		exec->stdsave[0] = dup(0);
		exec->stdsave[1] = dup(1);
		inout_before_proc(start, exec);
		builtin_process(exec, elem_lst);
		if (exec->stdsave[0] >= 0)
			dup_close_zero(exec);
		if (exec->stdsave[1] >= 0)
			dup_close_one(exec);
	}
	else
	{
		pipe_proc(start, elem_lst, exec);
		if (exec->infile >= 0)
			close(exec->infile);
		wait_loop(exec);
	}
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
	open_heredoc(g_data.parser_lst);
	main_loop(exec);
	g_data.exec_struct = exec;
}

void	read_input(t_data *data)
{
	printf("input = %s\n", data->input);
	lexer(data);
	data->lexer_lst = expend();
	print_lst(g_data.lexer_lst);
	if (error_token(data))
	{
		parser();
		executer();
	}
}

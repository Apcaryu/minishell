/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:52:16 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/09 18:45:00 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

extern t_data	g_data;

// ~ OPEN
int	open_inout(t_elem_pars *elem, t_exec *exec)
{
	int	file;

	file = -1;
	if (elem->args != NULL && elem->type == INFILE)
	{
		file = open(elem->args[0], O_RDONLY, 0644);
		if (file == -1)
		{
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(0);
		}
	}
	else if (elem->args != NULL && elem->type == OUTFILE)
	{
		file = open(elem->args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file == -1)
		{
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(1);
		}
	}
	else if (elem->args != NULL && elem->type == APPEND)
	{
		file = open(elem->args[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (file == -1)
		{
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(1);
		}
	}
	else if (elem->args != NULL && elem->type == HEREDOC)
	{
		file = ft_heredoc(elem, exec);
	}
	return (file);
}

// ~ OPEN
void	child_open(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
{
	char	*cmd;
	int		infile;
	int		outfile;

	infile = -2;
	outfile = -2;
	while ((elem->next != NULL && start != elem) \
		|| (elem->next == NULL && start != NULL))
	{
		if (start->type == INFILE)
			infile = open_inout(start, exec);
		else if (start->type == COMMAND)
			cmd = start->cmd;
		else if (start->type == OUTFILE)
			outfile = open_inout(start, exec);
		else if (start->type == APPEND)
			outfile = open_inout(start, exec);
		else if (start->type == HEREDOC)
		{
			infile = open_inout(start, exec);
		}
		start = start->next;
	}
	close(exec->pipefd[0]);
	if (infile >= 0)
	{
		dprintf(2, "fd:%d\n", infile);
		dup2(infile, 0);
		close(infile);
	}
	else if (exec->infile >= 0)
	{
		dup2(exec->infile, 0);
		close(exec->infile);
	}
	if (outfile >= 0)
	{
		dup2(outfile, 1);
		close(outfile);
	}	
	else if (elem->type == PIPE && outfile == -2)
		dup2(exec->pipefd[1], 1);
	if (exec->nbr_cmd == 0)
		exit (0);
	close(exec->pipefd[1]);
}

// ~ OPEN
void	inout_before_proc(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
{
	char	*cmd;
	int		infile;
	int		outfile;

	infile = -2;
	outfile = -2;
	while ((elem->next != NULL && start != elem) \
		|| (elem->next == NULL && start != NULL))
	{
		if (start->type == INFILE)
			infile = open_inout(start, exec);
		else if (start->type == COMMAND)
			cmd = start->cmd;
		else if (start->type == OUTFILE)
			outfile = open_inout(start, exec);
		else if (start->type == APPEND)
			outfile = open_inout(start, exec);
		else if (start->type == HEREDOC)
			infile = open_inout(start, exec);
		start = start->next;
	}
	if (infile >= 0)
	{
		dup2(infile, 0);
		close(infile);
	}
	else
		close(exec->stdsave[0]);
	if (outfile >= 0)
	{
		dup2(outfile, 1);
		close(outfile);
	}
	else
		close(exec->stdsave[1]);
}

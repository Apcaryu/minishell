/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:52:16 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 16:45:15 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

extern t_data	g_data;

static int	infile_or_outfile(t_elem_pars *elem, t_exec *exec, int file)
{
	if (elem->args != NULL && elem->type == INFILE)
	{
		file = open(elem->args[0], O_RDONLY, 0644);
		if (file == -1)
			error_endl(1, g_data.parser_lst->args[0], strerror(errno));
	}
	else if (elem->args != NULL && elem->type == OUTFILE)
	{
		file = open(elem->args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file == -1)
			error_endl(1, g_data.parser_lst->args[0], strerror(errno));
	}
	return (file);
}

static int	append_or_heredoc(t_elem_pars *elem, t_exec *exec, int file)
{
	char			*here_file;
	char			*nb;
	char			*here_file_joined;
	static int		nb_hd = 0;

	if (elem->args != NULL && elem->type == APPEND)
	{
		file = open(elem->args[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (file == -1)
			error_endl(1, g_data.parser_lst->args[0], strerror(errno));
	}
	else if (elem->args != NULL && elem->type == HEREDOC)
	{
		nb = ft_itoa(nb_hd);
		here_file = ".here_doc";
		here_file_joined = ft_strjoin(here_file, nb);
		file = open(here_file_joined, O_RDONLY, 0644);
		if (file < 0)
			unlink(here_file_joined);
		nb_hd++;
	}
	return (file);
}

int	open_inout(t_elem_pars *elem, t_exec *exec)
{
	int				file;

	file = -1;
	file = infile_or_outfile(elem, exec, file);
	file = append_or_heredoc(elem, exec, file);
	return (file);
}

void	child_open(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
{
	char	*cmd;

	while ((elem->next != NULL && start != elem) \
		|| (elem->next == NULL && start != NULL))
	{
		if (start->type == INFILE)
			exec->infile = open_inout(start, exec);
		else if (start->type == COMMAND)
			cmd = start->cmd;
		else if (start->type == OUTFILE)
			exec->outfile = open_inout(start, exec);
		else if (start->type == APPEND)
			exec->outfile = open_inout(start, exec);
		else if (start->type == HEREDOC)
			exec->infile = open_inout(start, exec);
		start = start->next;
	}
	close(exec->pipefd[0]);
	file_dup(exec->infile, 0);
	file_dup(exec->outfile, 1);
	if (elem->type == PIPE && exec->outfile < 0)
		dup2(exec->pipefd[1], 1);
	if (exec->nbr_cmd == 0)
		exit (0);
	close(exec->pipefd[1]);
}

void	inout_before_proc(t_elem_pars *start, t_exec *exec)
{
	char	*cmd;

	while (start != NULL)
	{
		if (start->type == INFILE)
			exec->infile = open_inout(start, exec);
		else if (start->type == COMMAND)
			cmd = start->cmd;
		else if (start->type == OUTFILE)
			exec->outfile = open_inout(start, exec);
		else if (start->type == APPEND)
			exec->outfile = open_inout(start, exec);
		else if (start->type == HEREDOC)
			exec->infile = open_inout(start, exec);
		start = start->next;
	}
	file_dup(exec->infile, 0);
	if (exec->infile < 0)
		close(exec->stdsave[0]);
	file_dup(exec->outfile, 1);
	if (exec->outfile < 0)
		close(exec->stdsave[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:52:16 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/10 16:35:06 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

extern t_data	g_data;

static void	infile_or_outfile(t_elem_pars *elem, t_exec *exec, int	*file)
{
	if (elem->args != NULL && elem->type == INFILE)
	{
		file[0] = open(elem->args[0], O_RDONLY, 0644);
		if (file[0] == -1)
		{
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(0);
		}
		file[1] = 1;
	}
	else if (elem->args != NULL && elem->type == OUTFILE)
	{
		file[0] = open(elem->args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file[0] == -1)
		{
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(1);
		}
		file[1] = 2;
	}
}

static void	append_or_heredoc(t_elem_pars *elem, t_exec *exec, int	*file)
{
	if (elem->args != NULL && elem->type == APPEND)
	{
		file[0] = open(elem->args[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (file[0] == -1)
		{
			error_msgs(g_data.parser_lst->args[0], strerror(errno));
			write(2, "\n", 1);
			exit(1);
		}
		file[1] = 2;
	}
	else if (elem->args != NULL && elem->type == HEREDOC)
	{
		file[0] = ft_heredoc(elem, exec);
		file[1] = 1;
	}
}

// ~ OPEN
void	open_inout(t_elem_pars *elem, t_exec *exec, int *file)
{
	infile_or_outfile(elem, exec, file);
	append_or_heredoc(elem, exec, file);
}

// ~ OPEN
void	child_open(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
{
	char	*cmd;
	int		file[2];

	file[0] = 0;
	file[1] = 0;
	while ((elem->next != NULL && start != elem) \
		|| (elem->next == NULL && start != NULL))
	{
		open_inout(start, exec, file);
		start = start->next;
	}
	close(exec->pipefd[0]);
	if (file[1] == 1)
	{
		dup2(file[0], 0);
		close(file[0]);
	}
	else if (exec->infile >= 0)
	{
		dup2(exec->infile, 0);
		close(exec->infile);
	}
	if (file[1] == 2)
	{
		dup2(file[0], 1);
		close(file[0]);
	}	
	else if (elem->type == PIPE && file[0] != 2)
		dup2(exec->pipefd[1], 1);
	if (exec->nbr_cmd == 0)
		exit (0);
	close(exec->pipefd[1]);
}

// ~ OPEN
void	inout_before_proc(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
{
	char	*cmd;
	int		file[2];

	file[0] = 0;
	file[1] = 0;
	while ((elem->next != NULL && start != elem) \
		|| (elem->next == NULL && start != NULL))
	{
		open_inout(start, exec, file);
		start = start->next;
	}
	if (file[1] == 1)
	{
		dup2(file[0], 0);
		close(file[0]);
	}
	else
		close(exec->stdsave[0]);
	if (file[1] == 2)
	{
		dup2(file[0], 1);
		close(file[0]);
	}
	else
		close(exec->stdsave[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:52:16 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/13 20:23:17 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

extern t_data	g_data;

// static void	infile_or_outfile(t_elem_pars *elem, t_exec *exec, int	*file)
// {
// 	if (elem->args != NULL && elem->type == INFILE)
// 	{
// 		file[0] = open(elem->args[0], O_RDONLY, 0644);
// 		if (file[0] == -1)
// 		{
// 			error_msgs(g_data.parser_lst->args[0], strerror(errno));
// 			write(2, "\n", 1);
// 			exit(0);
// 		}
// 		file[1] = 1;
// 	}
// 	if (elem->args != NULL && elem->type == OUTFILE)
// 	{
// 		file[0] = open(elem->args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 		if (file[0] == -1)
// 		{
// 			error_msgs(g_data.parser_lst->args[0], strerror(errno));
// 			write(2, "\n", 1);
// 			exit(1);
// 		}
// 		file[1] = 2;
// 	}
// }

// static void	append_or_heredoc(t_elem_pars *elem, t_exec *exec, int	*file)
// {
// 	if (elem->args != NULL && elem->type == APPEND)
// 	{
// 		file[0] = open(elem->args[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
// 		if (file[0] == -1)
// 		{
// 			error_msgs(g_data.parser_lst->args[0], strerror(errno));
// 			write(2, "\n", 1);
// 			exit(1);
// 		}
// 		file[1] = 2;
// 	}
// 	else if (elem->args != NULL && elem->type == HEREDOC)
// 	{
// 		file[0] = ft_heredoc(elem, exec);
// 		file[1] = 1;
// 	}
// }

// ~ OPEN
// void	open_inout(t_elem_pars *elem, t_exec *exec, int *file)
// {
// 	infile_or_outfile(elem, exec, file);
// 	append_or_heredoc(elem, exec, file);
// }

int	open_inout(t_elem_pars *elem, t_exec *exec)
{
	int				file;
	char			*here_file;
	char			*nb;
	char			*here_file_joined;
	static int		nb_hd = 0;

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
		nb = ft_itoa(nb_hd);
		here_file = ".here_doc";
		here_file_joined = ft_strjoin(here_file, nb);
		// file = ft_heredoc(elem, exec);
		file = open(here_file_joined, O_RDONLY, 0644);
		if (file < 0)
			unlink(here_file_joined);
		nb_hd++;
		return (file);
	}
	return (file);
}

// ~ OPEN
// void	child_open(t_elem_pars *start, t_elem_pars *elem, t_exec *exec)
// {
// 	char	*cmd;
// 	int		file[2];

// 	file[0] = 0;
// 	file[1] = 0;
// 	while ((elem->next != NULL && start != elem) \
// 		|| (elem->next == NULL && start != NULL))
// 	{
// 		open_inout(start, exec, file);
// 		start = start->next;
// 	}
// 	close(exec->pipefd[0]);
// 	child_open_utils(exec, file[1], file[0]);
// 	if (file[1] == 2)
// 	{
// 		dup2(file[0], 1);
// 		close(file[0]);
// 	}	
// 	else if (elem->type == PIPE && file[0] != 2)
// 		dup2(exec->pipefd[1], 1);
// 	if (exec->nbr_cmd == 0)
// 		exit (0);
// 	close(exec->pipefd[1]);
// }

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
// void	inout_before_proc(t_elem_pars *start, t_exec *exec)
// {
// 	char	*cmd;
// 	int		file[2];

// 	file[0] = -1;
// 	file[1] = -1;
// 	while (start != NULL)
// 	{
// 		open_inout(start, exec, file);
// 		start = start->next;
// 	}
// 	if (file[1] == 1)
// 	{
// 		dup2(file[0], 0);
// 		close(file[0]);
// 	}
// 	else
// 		close(exec->stdsave[0]);
// 	if (file[1] == 2)
// 	{
// 		dup2(file[0], 1);
// 		close(file[0]);
// 	}
// 	else
// 		close(exec->stdsave[1]);
// }

void	inout_before_proc(t_elem_pars *start, t_exec *exec)
{
	char	*cmd;
	int		infile;
	int		outfile;

	infile = -2;
	outfile = -2;
	while (start != NULL)
	{
		dprintf(2, "Passer %p\n", start);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:36:59 by meshahrv          #+#    #+#             */
/*   Updated: 2023/01/14 14:37:41 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

void	close_fd(t_exec *exec)
{
	close(exec->pipefd[0]);
	close(exec->pipefd[1]);
	close(exec->infile);
}

int exiteur(int exit_code, t_exec *exec)
{
	close(exec->pid);
	// ft_lstclear(&g_data.garb_lst, &free);
	// exit(exit_code);
	return (exit_code);
}
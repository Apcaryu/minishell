/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:36:59 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/15 20:50:45 by meshahrv         ###   ########.fr       */
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

int	exiteur(int exit_code, t_exec *exec)
{
	close(exec->pid);
	return (exit_code);
}

char	**clean_cmds(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str && str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
	return (NULL);
}

void	wait_loop(t_exec *exec)
{
	if (exec->pipefd[0] >= 0)
		close(exec->pipefd[0]);
	if (exec->pipefd[1] >= 0)
		close(exec->pipefd[1]);
	while (errno != ECHILD)
	{
		wait(&exec->pid);
		if (WIFEXITED(exec->status))
			exec->exit_code = WEXITSTATUS(exec->status);
	}
}

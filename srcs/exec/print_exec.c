/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:14:45 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 18:53:56 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

void	print_elem_lst(t_elem_pars *lst)
{
	if (lst == NULL)
		return ;
	printf("elem = %p | type = %d | cmd = %s | arg = %s \
		| next %p\n", lst, lst->type, lst->cmd, lst->args[0], lst->next);
	lst = lst->next;
	printf("elem = %p | type = %d | cmd = %s \
		| next %p\n", lst, lst->type, lst->cmd, lst->next);
	lst = lst->next;
	printf("elem = %p | type = %d | cmd = %s \
		| next %p\n", lst, lst->type, lst->cmd, lst->next);
	lst = lst->next;
	printf("elem = %p | type = %d | cmd = %s \
		| next %p\n", lst, lst->type, lst->cmd, lst->next);
	lst = lst->next;
	printf("elem = %p | type = %d | cmd = %s | arg = %s \
		| next %p\n", lst, lst->type, lst->cmd, lst->args[0], lst->next);
}

void	print_exec_struct(t_exec *exec)
{
	if (exec == NULL)
		return ;
	printf("exec structure = %p | pid = %d | pipefd[0] = %d \
		| pipefd[1] = %d\n", exec, exec->pid->pid, \
		exec->pipefd[0], exec->pipefd[1]);
}

void	error_msgs(char *cmd, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
}

void	error_endl(int exit_nbr, char *cmd, char *err)
{
	int	i;

	error_msgs(cmd, err);
	write(2, "\n", 1);
	ft_lstclear(&g_data.garb_lst, &free);
	i = 2;
	while (++i < 123)
		close(i);
	ft_lstclear(&g_data.garb_lst, &free);
	g_data.exit_code = exit_nbr;
	exit(g_data.exit_code);
}

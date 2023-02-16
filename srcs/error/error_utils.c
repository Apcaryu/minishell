/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:19:06 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/16 19:11:07 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/error_msg.h"

void	init_process_validate(t_process_validation *check_proc)
{
	check_proc->redirection = false;
	check_proc->infile = false;
	check_proc->cmd = false;
	check_proc->pipe = false;
}

t_bool	print_syntax_error(void)
{
	printf("minishell: syntax error\n");
	return (false);
}

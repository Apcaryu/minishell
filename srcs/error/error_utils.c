/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:19:06 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/14 19:19:08 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/error_msg.h"

void	init_process_validate(t_process_validation *check_proc)
{
	check_proc->infile = false;
	check_proc->cmd = false;
	check_proc->pipe = false;
}

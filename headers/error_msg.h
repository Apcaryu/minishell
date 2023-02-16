/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:24:15 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/13 15:24:17 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H
# include "main.h"

typedef struct s_process_validation
{
	t_bool	infile;
	t_bool	cmd;
	t_bool	pipe;
}	t_process_validation;

void	init_process_validate(t_process_validation *check_proc);
t_bool	error_token(t_data *data);

t_bool	is_empty_line(char *input);

#endif

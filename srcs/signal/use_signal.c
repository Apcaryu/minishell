/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:46:07 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/16 16:46:07 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/use_signal.h"

extern t_data	g_data;

void	ctrl_c(int code)
{
	g_data.exit_code = 130;
	if (g_data.is_interactive == true)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	ctrl_d(int code)
{
	return ;
}

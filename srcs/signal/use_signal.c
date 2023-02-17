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
	(void)code;
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

void	ctrl_c_here(int code)
{
	(void)code;
	g_data.exit_code = 130;
	close(g_data.tmp_fd);
	write(0, "\n", 1);
	return ;
}

void	ctrl_quit(int code)
{
	(void)code;
	if (!g_data.is_heredoc)
	{
		printf("Quit (core dump)\n");
		g_data.exit_code = 131;
	}
	else
	{
		write(0, "\b\b  \b\b", 6);
	}
}

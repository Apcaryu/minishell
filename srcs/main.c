/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:37:50 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 10:37:51 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/use_signal.h"
#include "../headers/error_msg.h"

t_data	g_data;

void	init_data(t_data *data, char **env)
{
	data->garb_lst = NULL;
	data->lexer_lst = NULL;
	data->parser_lst = NULL;
	data->exec_struct = NULL;
	data->env = env;
	data->env_bis = create_env(data->env);
	data->tab = convert_lst_to_tab(*data);
	data->exit_code = 0;
}

void	init_signal(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char *argv[], char **envp)
{
	init_data(&g_data, envp);
	init_signal();
	while (1)
	{
		g_data.is_interactive = true;
		g_data.input = readline("\033[38;5;140mminishell-0.1$ \033[0m");
		g_data.is_interactive = false;
		if (g_data.input == NULL)
		{
			ft_lstclear(&g_data.garb_lst, &free);
			exit(127);
		}
		add_history(g_data.input);
		read_input(&g_data);
		free(g_data.input);
		g_data.lexer_lst = NULL;
		g_data.parser_lst = NULL;
		g_data.exec_struct = NULL;
		g_data.input = NULL;
	}
	if (g_data.garb_lst != NULL)
		ft_lstclear(&g_data.garb_lst, &free);
	return (0);
}

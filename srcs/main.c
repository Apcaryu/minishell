#include "../headers/minishell.h"
#include "../headers/use_signal.h"

t_data g_data;

void	init_data(t_data *data, char **env)
{
	data->garb_lst = NULL;
	data->lexer_lst = NULL;//new_token(&data->garb_lst);
	data->parser_lst = NULL;
	data->exec_struct = NULL;
	data->env = env;
	if (*env == NULL)
	{
		// TODO : si env -i, afficher les 3 lignes (!env[0] a tester si jamais)
		/*
		PWD=/mnt/nfs/homes/meshahrv/Documents/Circle_3/MINISHELL_GIT
		SHLVL=1
		_=/usr/bin/env
		*/
	}
	data->env_bis = create_env(data->env);
	data->tab = convert_lst_to_tab(*data);
}

void	init_signal(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char *argv[], char  **envp)
{
//	t_data data;

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
		// free(g_data.lexer_lst);
		ft_lstclear(&g_data.garb_lst, &free);
		// printf("case_lex = %p | type = %d\n", g_data.lexer_lst, g_data.lexer_lst->type);
		free(g_data.input);
//		g_data.lexer_lst = NULL;
		g_data.lexer_lst = NULL;
		g_data.parser_lst = NULL;
		g_data.exec_struct = NULL;
		g_data.input = NULL;
		ft_lstclear(&g_data.garb_lst, &free);
	}
	return(0);
}
#include "../headers/minishell.h"

t_data g_data;

void	init_data(t_data *data)
{
	data->garb_lst = NULL;
	data->lexer_lst = NULL;//new_token(&data->garb_lst);
}

int	main(int argc, char *argv[], char  **envp)
{
//	t_data data;

	init_data(&g_data);
	while (1)
	{
		g_data.input = readline("minishell-0.1$ ");
		read_input(&g_data);
		ft_lstclear(&g_data.garb_lst, &free);
		free(g_data.input);
	}
	
	return(0);
}
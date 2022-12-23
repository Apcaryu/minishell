#include "../headers/minishell.h"

void	init_data(t_data *data)
{
	data->garb_lst = NULL;
	data->lexer_lst = NULL;//new_token(&data->garb_lst);
}

int	main(int argc, char *argv[], char  **envp)
{
	t_data data;

	init_data(&data);
	while (1)
	{
		data.input = readline("minishell-0.1$ ");
		read_input(&data);
		ft_lstclear(&data.garb_lst, &free);
		free(data.input);
	}
	
	return(0);
}
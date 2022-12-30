#include "../headers/minishell.h"

t_data g_data;

void	init_data(t_data *data)
{
	data->garb_lst = NULL;
	data->nlexer_lst = NULL;
}

int	main(int argc, char *argv[], char  **envp)
{
//	t_data data;

	init_data(&g_data);
	while (1)
	{
		g_data.input = readline("minishell-0.1$ ");
		read_input(&g_data);
		// free(g_data.lexer_lst);
		ft_lstclear(&g_data.garb_lst, &free);
		// printf("case_lex = %p | type = %d\n", g_data.lexer_lst, g_data.lexer_lst->type);
		free(g_data.input);
//		g_data.lexer_lst = NULL;
		g_data.nlexer_lst = NULL;
		g_data.parser_lst = NULL;
		g_data.input = NULL;
	}
	
	return(0);
}
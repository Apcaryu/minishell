#include "../headers/minishell.h"

int	main(int argc, char *argv[])
{
	char *	input;

	while (1)
	{
		input = readline("minishell-0.1$ ");
		read_input(input);
		free(input);
	}
	
	return(0);
}
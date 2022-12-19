#include "../headers/minishell.h"

int	main(int argc, char *argv[])
{
	char *	input;

	while (1)
	{
		input = readline("minishell-0.1$ ");
		printf("input = %s\n", input);
		free(input);
	}
	
	return(0);
}
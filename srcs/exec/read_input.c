#include "../../headers/exec.h"

void	check_command(char *input)
{
	if (!ft_strncmp("echo", input, ft_strlen("echo")))
		printf("output echo command\n");
}

void	read_input(char *input)
{
	printf("input = %s\n", input);
	check_command(input);
}
#include "../../headers/exec.h"

void	check_command(char *input)
{
	if (!ft_strncmp("echo", input, ft_strlen("echo")))
		echo_exec();
	else if (!ft_strncmp("cd", input, ft_strlen("cd")))
		cd_exec();
}

void	read_input(char *input)
{
	printf("input = %s\n", input);
	check_command(input);
}
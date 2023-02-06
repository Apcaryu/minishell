# include "../headers/use_signal.h"

extern t_data g_data;

void	ctrl_c(int code)
{
	if (g_data.is_interactive == true)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	ctrl_d(int code)
{
	return ;
}
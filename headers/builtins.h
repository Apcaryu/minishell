#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdio.h>
# include "main.h"

typedef enum e_builtins
{
	echo = 0,
	cd = 1,
	pwd = 2,
	export = 3,
	unset = 4,
	env = 5,
	// exit = 6
}	t_builtins;

void	echo_exec(void);
void	cd_exec(void);
void	pwd_exec(void);
void	export_exec(char *str);
void	unset_exec(void);
void	env_exec(void);
void	exit_exec(t_exec *exec);

#endif
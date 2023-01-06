#ifndef EXEC_H
# define EXEC_H
# include <stdio.h>
# include "main.h"
//# include "../libft_42/includes_libft/libft.h"
//# include "lexer.h"
# include "builtins.h"

void	read_input(t_data *data);

t_exec *new_exec(t_list **garb_list);
t_exec *exec_last(t_exec *exec_lst);
void	exec_add_back(t_exec **exec_lst, t_exec *elem);

#endif
#ifndef EXEC_H
# define EXEC_H
# include <stdio.h>
# include "main.h"
//# include "../libft_42/includes_libft/libft.h"
//# include "lexer.h"
# include "builtins.h"

// Exec functions
void	check_command(char *input);
void	read_input(t_data *data);
void	pipe_process(t_exec *exec);
int		main_loop(t_exec *exec);
void	executer(void);

// Close fds
void	close_fd(t_exec *exec);

// Init exec
void		init_test_exec();
void		open_inout_fds(t_exec *exec);
t_exec		*init_exec_structure(t_exec *exec);

// Print elements
void	print_elem_lst(t_elem_pars *lst); // TODO remove;
void	print_exec_struct(t_exec *exec); // TODO remove;

// Exec chain-lists
t_exec *new_exec(t_list **garb_list);
t_exec *exec_last(t_exec *exec_lst);
void	exec_add_back(t_exec **exec_lst, t_exec *elem);

#endif
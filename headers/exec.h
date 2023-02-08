/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:18:10 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/08 16:56:17 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include <stdio.h>
# include "main.h"
//# include "../libft_42/includes_libft/libft.h"
//# include "lexer.h"
# include "builtins.h"

// builtin_process.c
t_bool	is_builtin(char *cmd);
t_bool	check_all_builtin(t_elem_pars *elem);
void	builtin_process(t_exec *exec, t_elem_pars *elem);

void		check_builtin(char *input);

// heredoc_process.c
void	read_line_heredoc(int fd, t_elem_pars *elem, t_exec *exec);
int	ft_heredoc(t_elem_pars *elem, t_exec *exec);

// Exec functions
void		read_input(t_data *data);
void		executer(void);
void		main_loop(t_exec *exec);

// Open Infile & Outfile
int	open_inout(t_elem_pars *elem, t_exec *exec);

// Pipes And Commands
void		child(t_elem_pars *start, t_elem_pars *elem, t_exec *exec, int i);
void		wait_loop(t_exec *exec);

// Close fds
void		close_fd(t_exec *exec);
char		**clean_cmds(char **str);

// Execution and Env PATH
char		**get_env(t_exec *exec);
void		exec_path(t_elem_pars *start, t_exec *exec);
void		exec_cmd(t_exec *exec, t_elem_pars *start, t_elem_pars *elem);

// Init exec
void		init_test_exec();
void		open_inout_fds(t_exec *exec, t_elem_pars *elem);
t_exec		*init_exec_structure(t_exec *exec);

// Print elements
void		print_elem_lst(t_elem_pars *lst); // TODO remove;
void		print_exec_struct(t_exec *exec); // TODO remove;
void		error_msgs(char *cmd, char *err);

// Exec chain-lists
t_exec		*new_exec(t_list **garb_list);
t_exec		*exec_last(t_exec *exec_lst);
void		exec_add_back(t_exec **exec_lst, t_exec *elem);


// Env utils
void	    free_env(t_env *env);
void	    add_env_line(t_env *env, t_env *new);
t_env       *create_env(char **env);
t_env       *new_env_line(char *env_line);

char	    **convert_lst_to_tab(t_data data);

#endif
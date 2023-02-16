/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:18:10 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 07:13:34 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include <stdio.h>
# include "main.h"
# include "builtins.h"

# define NAR "numeric argument required\n"
# define TMA "too many arguments\n"

// builtin_process.c
t_bool		is_builtin(char *cmd);
t_bool		check_all_builtin(t_elem_pars *elem);
void		builtin_process(t_exec *exec, t_elem_pars *elem);

// heredoc_process.c
void		read_line_heredoc(int fd, t_elem_pars *elem);
char		*ft_heredoc(t_elem_pars *elem, int nb_hd);
void		open_heredoc(t_elem_pars *elem);

// Exec functions
void		read_input(t_data *data);
void		executer(void);
void		main_loop(t_exec *exec);

// open_fds.c
int			open_inout(t_elem_pars *elem, t_exec *exec);
void		child_open(t_elem_pars *start, t_elem_pars *elem, t_exec *exec);
void		inout_before_proc(t_elem_pars *start, t_exec *exec);

// pipe_process.c
void		child_process(t_elem_pars *start, \
							t_elem_pars *elem_lst, t_exec *exec);
void		pipe_proc(t_elem_pars *start, t_elem_pars *elem, t_exec *exec);

// close_and_exit.c
void		close_fd(t_exec *exec);
char		**clean_cmds(char **str);
void		wait_loop(t_exec *exec);

// exec_utils.c
void		file_dup(int file, int dupnbr);

// Pipes And Commands
void		child_open(t_elem_pars *start, t_elem_pars *elem, t_exec *exec);

// Execution and Env PATH
char		**get_env(t_exec *exec);
void		exec_path(t_elem_pars *start, t_exec *exec);
void		exec_cmd(t_exec *exec, t_elem_pars *start, t_elem_pars *elem);

// Init exec
void		open_inout_fds(t_exec *exec, t_elem_pars *elem);
t_exec		*init_exec_structure(t_exec *exec);

// Print elements
void		print_elem_lst(t_elem_pars *lst);
void		print_exec_struct(t_exec *exec);
void		error_msgs(char *cmd, char *err);
void		error_endl(int exit_nbr, char *cmd, char *err);

// Env utils
void		free_env(t_env *env);
void		add_env_line(t_env *env, t_env *new);
t_env		*create_env(char **env);
t_env		*new_env_line(char *env_line);
int			env_len(int len, t_env *env);

char		**convert_lst_to_tab(t_data data);

#endif

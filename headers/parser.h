#ifndef PARSER_H
# define PARSER_H
# include "main.h"

void	p_token(t_token *token);
void	p_elem(t_elem_pars *elem);
void	p_lst_elem(t_elem_pars *lst);

t_bool	is_in_here_out_append(t_type type);
t_elem_pars	*init_command_elem(void);
t_token	*move_tlst(t_token *lex_lst, unsigned int nb_move);
t_token	*space_jump(t_token *lex_lst);
void	add_elem(t_data *data, t_elem_pars *elem);

t_elem_pars *new_elem_pars(t_list **garb_list);
t_elem_pars *elem_pars_last(t_elem_pars *elem_lst);
void	elem_pars_add_back(t_elem_pars **elem_lst, t_elem_pars *elem);

void	parser(void);

#endif

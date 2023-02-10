#ifndef PARSER_H
# define PARSER_H
# include "main.h"

void	p_token(t_token *token);
void	p_elem(t_elem_pars *elem);
void	p_lst_elem(t_elem_pars *lst);

t_elem_pars *new_elem_pars(t_list **garb_list);
t_elem_pars *elem_pars_last(t_elem_pars *elem_lst);
void	elem_pars_add_back(t_elem_pars **elem_lst, t_elem_pars *elem);

void	parser(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:38:32 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/16 16:38:32 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "main.h"

typedef struct s_arg_count
{
	unsigned int	nb_move;
	unsigned int	*idx;
}	t_arg_count;

void			p_token(t_token *token);
void			p_elem(t_elem_pars *elem);
void			p_lst_elem(t_elem_pars *lst);

t_bool			is_in_here_out_append(t_type type);
t_elem_pars		*init_command_elem(void);
t_token			*move_tlst(t_token *lex_lst, unsigned int nb_move);
t_token			*space_jump(t_token *lex_lst);
void			add_elem(t_data *data, t_elem_pars *elem);

unsigned int	ncommand(t_elem_pars *elem_pars, t_token *token);

unsigned int	content_fusion_cmd(t_token *token_lst, t_elem_pars *elem, \
									unsigned int nb_move);
char			*fusion_arg(t_token *token_lst, char *arg, \
							unsigned int *nb_move);

unsigned int	set_elem(t_elem_pars *elem_pars, t_token *token, \
							t_elem_pars *cmd_elem, unsigned int *idx);

t_elem_pars		*new_elem_pars(t_list **garb_list);
t_elem_pars		*elem_pars_last(t_elem_pars *elem_lst);
void			elem_pars_add_back(t_elem_pars **elem_lst, t_elem_pars *elem);

void			parser(void);

#endif

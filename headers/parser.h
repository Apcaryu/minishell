#ifndef PARSER_H
# define PARSER_H
# include "main.h"
//# include "../libft_42/includes_libft/libft.h"
//# include "../libft_42/includes_libft/garbage.h"
//# include "minishell.h"
//# include "lexer.h"
//# include "exec.h"

//typedef struct s_elem_pars
//{
//	t_type				type;
//	char				*cmd;
//	char				**args;
//	struct s_elem_pars	*next;
//}	t_elem_pars;
//
//# ifndef T_DATA
//#  define T_DATA
//
//typedef struct s_data
//{
//	char *input;
//	t_list *garb_lst;
//	t_token *lexer_lst;
//	t_elem_pars	*parser_lst;
//}	t_data;
//# endif

t_elem_pars *new_elem_pars(t_list **garb_list);
t_elem_pars *elem_pars_last(t_elem_pars *elem_lst);
void	elem_pars_add_back(t_elem_pars **elem_lst, t_elem_pars *elem);

void	parser(void);

#endif
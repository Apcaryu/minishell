#include "../../headers/parser.h"

extern t_data g_data;

t_nelem *new_elem_pars(t_list **garb_list)
{
	t_nelem  *new;

	new = garbage_alloc(garb_list, sizeof(t_nelem));
	if (new == NULL)
		return (NULL);
	new->type = NONE;
	new->cmd = NULL;
	new->args = NULL;
	new->next = NULL;
	return (new);
}

t_nelem *elem_pars_last(t_nelem *elem_lst)
{
	if (elem_lst != NULL)
	{
		while (elem_lst->next != NULL)
			elem_lst = elem_lst->next;
	}
	return (elem_lst);
}

void	elem_pars_add_back(t_nelem **elem_lst, t_nelem *elem)
{
	t_nelem *last_elem_pars;

	if (!elem_lst || !elem)
		return ;
	last_elem_pars = elem_pars_last(*elem_lst);
	if (!last_elem_pars)
		*elem_lst = elem;
	else
		last_elem_pars->next = elem;
}

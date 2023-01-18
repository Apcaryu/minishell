#include "../../headers/minishell.h"

extern t_data g_data;

t_exec *new_exec(t_list **garb_list)
{
	t_exec  *new;

	new = garbage_alloc(garb_list, sizeof(t_exec));
	if (new == NULL)
		return (NULL);
	// new->type = NONE;
	new->cmd = NULL;
	new->args = NULL;
	new->next = NULL;
	return (new);
}

t_exec *exec_last(t_exec *exec_lst)
{
	if (exec_lst != NULL)
	{
		while (exec_lst->next != NULL)
			exec_lst = exec_lst->next;
	}
	return (exec_lst);
}

void	exec_add_back(t_exec **exec_lst, t_exec *elem)
{
	t_exec *last_exec;

	if (!exec_lst || !elem)
		return ;
	last_exec = exec_last(*exec_lst);
	if (!last_exec)
		*exec_lst = elem;
	else
		last_exec->next = elem;
}
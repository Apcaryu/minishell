#include "lexer.h"

t_token *new_token(t_list **garb_lst)
{
	t_token *new;

	new = garbage_alloc(garb_lst, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	return (new);
}

t_token *token_last(t_token *token_lst)
{
	if (token_lst != NULL)
	{
		while (token_lst->next != NULL)
			token_lst = token_lst->next;
	}
	return (token_lst);
}

void	token_add_back(t_token **token_lst, t_token *token)
{
	t_token *last_token;

	if (!token_lst || !token)
		return ;
	last_token = token_last(*token_lst);
	if (!last_token)
		*token_lst = token;
	else
		last_token->next = token;
}
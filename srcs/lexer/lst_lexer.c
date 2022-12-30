#include "../../headers/lexer.h"

extern t_data g_data;

//t_token *new_token(t_list **garb_lst)
//{
//	t_token *new;
//
//	new = garbage_alloc(garb_lst, sizeof(t_token) * 1);
//	if (new == NULL)
//		return (NULL);
//	new->next = NULL;
//	return (new);
//}
//
//t_token *token_last(t_token *token_lst)
//{
//	if (token_lst != NULL)
//	{
//		// p_lex_lst(token_lst);
//		while (token_lst->next != NULL)
//			// p_lex_lst(token_lst);
//			token_lst = token_lst->next;
//	}
//	return (token_lst);
//}
//
//void	token_add_back(t_token **token_lst, t_token *token)
//{
//	t_token *last_token;
//
//	// p_lex_lst(token);
//	if (!token_lst || !token)
//		return ;
//	last_token = token_last(*token_lst);
//	if (!last_token)
//		*token_lst = token;
//	else
//		last_token->next = token;
//}

// ---------- NEW LST_LEXER ---------- //
t_ntoken	*new_ntoken(t_list **garb_lst)
{
	t_ntoken *new;

	return (new);
}

t_ntoken *ntoken_last(t_ntoken *token_lst)
{
	return (token_lst);
}

void	ntoken_add_back(t_ntoken **token_lst, t_ntoken *token)
{
	return ;
}
// ---------- END ---------- //
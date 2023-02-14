/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:24:31 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/13 15:24:33 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/error_msg.h"

void	init_process_validate(t_process_validation *check_proc)
{
	check_proc->infile = true;
	check_proc->outfile = true;
	check_proc->pipe = true;
}

t_bool	check_redirect(t_token *token, t_process_validation *check_proc)
{
	if(token->next == NULL)
	{
		check_proc->infile = false;
		printf("unexpected token\n");
		return (false);
	}
	token = token->next;
	if (token->type == C_SPACE)
	{
		token = token->next;
	}
	if (token->type == COMMAND)
		return (true);
	else
	{
		printf("unexpected token\n");
		return (false);
	}
}

t_bool	check_pipe(t_token *token, t_process_validation *check_proc)
{
	if (token->next == NULL)
	{
		check_proc->pipe = false;
		printf("unexpected token\n");
		return (false);
	}
	token = token->next;
	if (token->type == C_SPACE)
		token = token->next;
	if (token == NULL)
	{
		printf("unexpected token\n");
		return (false);
	}
	else
		return (true);
}

t_bool	check_token(t_token *token, t_process_validation *check_proc)
{
	if (token->type == INFILE || token->type == HEREDOC || \
	token->type == OUTFILE || token->type == APPEND)
		return (check_redirect(token, check_proc));
	else if (token->type == PIPE)
		return (check_pipe(token, check_proc));
	else
		return (true);
}

t_bool	error_token(t_data *data)
{
	t_bool	error_detected;
	t_process_validation check_proc;
	t_token	*token_lst;

	error_detected = true;
	init_process_validate(&check_proc);
	token_lst = data->lexer_lst;
	while (token_lst != NULL)
	{
		error_detected = check_token(token_lst, &check_proc);
		if (!error_detected)
		{
			data->exit_code = 2;
			return (error_detected);
		}
		if (token_lst == NULL)
			break ;
		else
			token_lst = token_lst->next;
	}
	return (error_detected);
}

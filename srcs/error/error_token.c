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

t_bool	check_redirect(t_token *token, t_process_validation *check_proc)
{
	if (token->next == NULL)
	{
		printf("minishell: syntax error\n");
		return (false);
	}
	token = token->next;
	while (token->type == C_SPACE)
	{
		token = token->next;
		if (token == NULL)
		{
			printf("minishell: syntax error\n");
			return (false);
		}
	}
	if (token->type == COMMAND || token->type == VARIABLE)
	{
		check_proc->infile = true;
		return (true);
	}
	else
	{
		printf("minishell: syntax error\n");
		return (false);
	}
}

t_bool	check_pipe(t_token *token, t_process_validation *check_proc)
{
	if (check_proc->infile == false)
	{
		printf("minishell: syntax error\n");
		return (false);
	}
	if (token->next == NULL)
	{
		check_proc->pipe = false;
		printf("minishell: syntax error\n");
		return (false);
	}
	token = token->next;
	if (token->type == C_SPACE)
		token = token->next;
	if (token == NULL)
	{
		printf("minishell: syntax error\n");
		return (false);
	}
	else
		return (true);
}

t_bool	check_quote(t_token *token)
{
	if (token->is_closed == false)
	{
		printf("minishell: syntax error\n");
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
	else if (token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
		return (check_quote(token));
	else if (token->type == COMMAND || token->type == VARIABLE)
	{
		check_proc->cmd = true;
		return (true);
	}
	else
		return (true);
}

t_bool	error_token(t_data *data)
{
	t_bool					error_detected;
	t_process_validation	check_proc;
	t_token					*token_lst;

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

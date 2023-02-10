/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:54:24 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/10 12:54:40 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

extern t_data	g_data;

char	*fusion_arg(t_token *token_lst, char *arg, unsigned int *nb_move)
{
	char	*tmp_content;

	arg = token_lst->content;
	if (token_lst->next == NULL)
		return (arg);
	else
		token_lst = token_lst->next;
	if (token_lst->type == COMMAND)
	{
		while (token_lst->type == COMMAND)
		{
			tmp_content = garbage_alloc(&g_data.garb_lst, \
			ft_strlen(arg) + ft_strlen(token_lst->content) + 1);
			ft_strlcpy(tmp_content, arg, ft_strlen(arg) + 1);
			ft_strlcat(tmp_content, token_lst->content, \
			ft_strlen(token_lst->content) + ft_strlen(tmp_content) + 1);
			arg = tmp_content;
			token_lst = token_lst->next;
			nb_move += 1;
			if (token_lst == NULL)
				break ;
		}
	}
	return (arg);
}

unsigned int	content_fusion_cmd(t_token *token_lst, t_elem_pars *elem, \
unsigned int nb_move)
{
	char	*tmp_content;

	elem->cmd = token_lst->content;
	if (token_lst->next == NULL)
		return (nb_move);
	else
		token_lst = token_lst->next;
	if (token_lst->type == COMMAND)
	{
		while (token_lst->type == COMMAND)
		{
			tmp_content = garbage_alloc(&g_data.garb_lst, \
			ft_strlen(elem->cmd) + ft_strlen(token_lst->content) + 1);
			ft_strlcpy(tmp_content, elem->cmd, ft_strlen(elem->cmd) + 1);
			ft_strlcat(tmp_content, token_lst->content, \
			ft_strlen(token_lst->content) + ft_strlen(tmp_content) + 1);
			elem->cmd = tmp_content;
			token_lst = token_lst->next;
			nb_move++;
			if (token_lst == NULL)
				break ;
		}
	}
	return (nb_move);
}

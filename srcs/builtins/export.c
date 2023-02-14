/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:30:03 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/13 18:02:55 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"
#include "../../headers/minishell.h"

extern t_data	g_data;

char	*get_syntax(char *str)
{
	int		i;
	int		size;
	char	*dest;

	if (str == NULL)
		return (str);
	size = ft_strlen(str);
	dest = NULL;
	i = 0;
	dest = ft_calloc(sizeof(char), ft_strlen(str) +1);
	ft_strlcpy(dest, str, size +1);
	return (dest);
}

int	env_line_already_exist(t_env *new)
{
	int		len;
	t_env	*head;

	len = 0;
	head = g_data.env_bis;
	while (new->line[len] && new->line[len] != '=')
		len++;
	while (head && ft_strncmp(head->line, new->line, len + 1) != 0)
		head = head->next;
	if (head == NULL)
		return (0);
	if (head->prev)
		head->prev->next = new;
	else
		g_data.env_bis = new;
	if (head->next)
		head->next->prev = new;
	new->prev = head->prev;
	new->next = head->next;
	free(head->line);
	free(head);
	return (1);
}

void	check_env_before_add(t_data data, t_env *new)
{
	if (!data.env_bis)
		data.env_bis = new;
	else
	{
		if (env_line_already_exist(new) == 0)
			add_env_line(data.env_bis, new);
	}
}

void	export_exec(char *str)
{
	int		i;
	char	*new_env;
	t_env	*new;
	t_data	data;

	data = g_data;
	new_env = get_syntax(str);
	if (!new_env)
		return ;
	new = new_env_line(new_env);
	if (!new)
	{
		free(new_env);
		return ;
	}
	free(new_env);
	check_env_before_add(data, new);
	data.tab = convert_lst_to_tab(data);
	if (!data.tab)
		return ;
	i = 0;
	while (data.tab[i + 1] != NULL)
		i++;
	if (g_data.tab)
		clean_cmds(g_data.tab);
	g_data.tab = data.tab;
}

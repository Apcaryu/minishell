/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:20:26 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 07:19:18 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/builtins.h"
#include "../../headers/minishell.h"

extern t_data	g_data;

t_bool	is_not_a_variable(char *str)
{
	while (str && *str)
	{
		if (*str == '=')
			return (false);
		str++;
	}
	return (true);
}

void	unset_first_node(t_env *node_to_unset, t_data *data)
{
	node_to_unset = data->env_bis;
	data->env_bis = data->env_bis->next;
	if (data->env_bis)
		data->env_bis->prev = NULL;
	free(node_to_unset->line);
	free(node_to_unset);
}

void	unset_right_node(t_env *env, t_env *node_to_unset)
{
	node_to_unset = env;
	env->prev->next = node_to_unset->next;
	if (env->next != NULL)
		env->next->prev = node_to_unset->prev;
}

void	unset_node(t_data *data, char *str)
{
	t_env	*env;
	int		len;
	t_env	*node_to_unset;

	len = 0;
	env = data->env_bis;
	node_to_unset = NULL;
	while (env->line[len] && env->line[len] != '=')
		len++;
	if (env && ft_strncmp(env->line, str, len + 1) == 0)
		unset_first_node(node_to_unset, data);
	else
	{
		while (env)
		{
			len = 0;
			len = env_len(len, env);
			if (ft_strncmp(env->line, str, len) == 0)
			{
				unset_right_node(env, node_to_unset);
				break ;
			}
			env = env->next;
		}
	}
}

void	unset_exec(char *str)
{
	int		i;
	t_data	data;
	char	*tmp;

	i = 0;
	tmp = str;
	data = g_data;
	if (!data.env_bis || !is_not_a_variable(str))
		return ;
	while (tmp[i])
	{
		if (tmp[i] && tmp[0] == '_' && !tmp[1])
			return ;
		i++;
	}
	unset_node(&data, str);
	data.tab = convert_lst_to_tab(data);
	g_data.tab = data.tab;
}

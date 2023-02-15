/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:40:41 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/15 18:26:36 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

t_env	*new_env_line(char *env_line)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->line = ft_strdup(env_line);
	env->prev = NULL;
	env->next = NULL;
	return (env);
}

void	free_env(t_env *env)
{
	t_env	*current;

	while (env)
	{
		current = env;
		env = env->next;
		free(current->line);
		free(current);
	}
}

void	add_env_line(t_env *env, t_env *new)
{
	while (env && env->next)
		env = env->next;
	new->prev = env;
	new->next = NULL;
	env->next = new;
}

t_env	*create_env(char **env)
{
	t_env	*head;
	t_env	*new;

	head = NULL;
	while (*env)
	{
		new = new_env_line(*env);
		// set_garb_lst(&g_data.garb_lst, new);
		if (!new)
		{
			if (head)
				free_env(head);
			return (NULL);
		}
		if (!head)
			head = new;
		else
		{
			add_env_line(head, new);
		}
		env++;
	}
	return (head);
}

int	env_len(int len, t_env *env)
{
	while (env->line[len] && env->line[len] != '=')
		len++;
	return (len);
}

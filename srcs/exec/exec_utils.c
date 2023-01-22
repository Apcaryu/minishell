#include "../../headers/minishell.h"

extern t_data	g_data;

t_env   *new_env_line(char *env_line)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if(!env)
		return (NULL);
	env->line = ft_strdup(env_line);
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
	// dprintf(2, "ICI\n");
	// dprintf(2, "env = %p\n", env);
	while (env && env->next)
	{
		env = env->next;
	}
	new->next = NULL;
	env->next = new;
}

t_env   *create_env(char **env)
{
	t_env   *head;
	t_env   *new;

	head = NULL;
	while (*env)
	{
		new = new_env_line(*env);
		// dprintf(2, "env = %p\n", env);

		// dprintf(2, "new line = %s\n", new->line);
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
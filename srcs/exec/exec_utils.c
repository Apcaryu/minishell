#include "../../headers/minishell.h"

extern t_data	g_data;

t_env   *new_env_line(char *env_line)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if(!env)
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
	// dprintf(2, "ICI\n");
	// dprintf(2, "new = %s\n", new->line);
	while (env && env->next)
	{
		// dprintf(2, "env = %p\n", env);
		env = env->next;
	}
	// dprintf(2, "env = %s\n", env->line);
	new->prev = env;
	// dprintf(2, "prev = %s\n", new->prev->line);
	new->next = NULL;
	env->next = new;
	// dprintf(2, "env->next = %s\n", env->next->line);
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

int	ft_lstenv_size(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

char	**convert_lst_to_tab(t_data data)
{
	t_env	*lst;
	char	**dest;
	int		i;

	dest = NULL;
	i = 0;
	lst = data.env_bis;
	dest = (char **)malloc(sizeof(char *) * (ft_lstenv_size(lst) + 1));
	if (!dest)
		return (NULL);
	while (lst)
	{
		dest[i] = ft_strdup(lst->line);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
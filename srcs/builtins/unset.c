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

void	unset_node(t_data *data, char *str)
{
	t_env	*env;
	t_env	*node_to_unset;

	env = data->env_bis;
	node_to_unset = NULL;
	if (env && ft_strncmp(env->line, str, ft_strlen(str)) == 0)
		unset_first_node(node_to_unset, data);
	else
	{
		while (env)
		{
			if (ft_strncmp(env->line, str, ft_strlen(str)) == 0)
			{
				node_to_unset = env;
				env->prev->next = node_to_unset->next;
				if (env->next != NULL)
					env->next->prev = node_to_unset->prev;
				free(node_to_unset->line);
				free(node_to_unset);
				break ;
			}
			env = env->next;
		}
	}
}

void	unset_exec(char *str)
{
	t_data	data;

	data = g_data;
	if (!data.env_bis || !is_not_a_variable(str))
	{
		// printf("%s : is not a variable\n", str);
		return ;
	}
	unset_node(&data, str);
	// dprintf(2, "UNSET\n");
	data.tab = convert_lst_to_tab(data);
	g_data.tab = data.tab;
}
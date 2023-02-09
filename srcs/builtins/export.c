#include "../../headers/builtins.h"
#include "../../headers/minishell.h"

extern t_data	g_data;

char	*get_syntax(char *str)
{
	int		i;
	char	*dest;
	int size;

	if (str == NULL)
		return (str);
	size = ft_strlen(str);
	dest = NULL;
	i = 0;
	// dprintf(2, "ICI\n");
	// dprintf(2, "str = %s\n", str);
	dest = ft_calloc(sizeof(char), ft_strlen(str) +1);
	ft_strlcpy(dest, str, size +1);
	return (dest);
}

int	env_line_already_exist(t_env *new)
{
	t_env	*head;
	int		len;

	len = 0;
	head = g_data.env_bis;
	while (new->line[len] && new->line[len] != '=')
		len++;
	while (head && ft_strncmp(head->line, new->line, len) != 0)
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

void	export_exec(char *str)
{

	// dprintf(2, "exec export\n");
	t_env	*new;
	char	*new_env;
	t_data	data;

	data = g_data;
	// dprintf(2, "ee str = %s\n", str);
	// dprintf(2, "export = %s\n", data.parser_lst->args[1]);
	new_env = get_syntax(str);
	// dprintf(2, "new_env = %s\n", new_env);
	// dprintf(2, "HALLOOOOwen\n");
	if (!new_env)
		return ;
	// dprintf(2, "new_env = %s\n", new_env);
	new = new_env_line(new_env);
	// dprintf(2, "new = %s\n", new->line);
	if (!new)
	{
		free(new_env);
		return ;
	}
	free(new_env);
	// dprintf(2, "env_bis = %s\n", data.env_bis->line);
	if (!data.env_bis)
		data.env_bis = new;
	else
	{
		// dprintf(2, "env_bis = %s\n", data.env_bis->line);
		if (env_line_already_exist(new) == 0)
			add_env_line(data.env_bis, new);
		// free_tab_str(&data->test, -1);
	}
	data.tab = convert_lst_to_tab(data);
	// dprintf(2, "tab = %s\n", *data.tab);
	if (!data.tab)
		return ;
	int i = 0;
	while (data.tab[i+1] != NULL)
		i++;
	// dprintf(2, "tab[ledernier] = %s | new.line = %s\n", data.tab[i], new->line);
	// g_data.env_bis = new;
	g_data.tab = data.tab;
	// dprintf(2, "tab[ledernier] = %s\n", g_data.tab[i]);
}
#include "../../headers/builtins.h"
#include "../../headers/minishell.h"

extern t_data	g_data;

void	add_char(char **actual, char c)
{
	int		i;
	char	*dest;

	dest = malloc(sizeof(char));
	// dprintf(2, "c = %c\n", c);
	// dprintf(2, "dest = %p\n", dest);
	if (!dest)
		return ;
	i = 0;
	while ((*actual) && (*actual)[i] != '\0')
	{
		// dprintf(2, "ICI\n");
		dest[i] = (*actual)[i];
		// dprintf(2, "dest[%d] = %c\n", i, dest[i]);
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	if (*actual)
		free(*actual);
	// dprintf(2, "dest = %s\n", dest);
	(*actual) = dest;
}

static void	get_string(char **dest, char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		add_char(dest, str[i]);
		i++;
	}
}

char	*get_syntax(char *str)
{
	int		i;
	char	*dest;

	dest = NULL;
	i = 0;
	dprintf(2, "ICI\n");
	dprintf(2, "str = %p\n", str);
	while (str[i] && str[i] != '=')
	{
		// dprintf(2, "str[%d] = %c\n", i, str[i]);
		add_char(&dest, str[i++]);
		// i++;
	}
	if (str[i] == '=')
		add_char(&dest, str[i++]);
	// dprintf(2, "dest = %s\n", dest);
	else
	{
		free(dest);
		return (0);
	}
	get_string(&dest, &str[i]);
	return (dest);
}

void	export_exec(char *str)
{
	dprintf(2, "exec export\n");
	t_env	*new;
	char	*new_env;

	// dprintf(2, "export = %s\n", g_data.parser_lst->args[1]);
	new_env = get_syntax(str);
	dprintf(2, "new_env = %s\n", new_env);
	if (!new_env)
		return ;
	new = new_env_line(new_env);
	dprintf(2, "new = %s\n", new->line);
	if (!new)
	{
		free(new_env);
		return ;
	}
	free(new_env);
	dprintf(2, "env_bis = %s\n", g_data.env_bis->line);
	if (!g_data.env_bis)
		g_data.env_bis = new;
}
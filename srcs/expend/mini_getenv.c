/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_getenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apellegr <apellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:42:05 by apellegr          #+#    #+#             */
/*   Updated: 2023/02/10 16:42:06 by apellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/expend.h"

unsigned int	chr_strlen(char *str, char limiter)
{
	unsigned int	idx;

	if (str == NULL)
		return (0);
	idx = 0;
	while (str[idx] != limiter && str[idx] != '\0')
		idx++;
	return (idx);
}

char	*get_value(t_data *data, char *var_name)
{
	char	*value_out;

	value_out = garbage_alloc(&data->garb_lst, ft_strlen(var_name) + 1);
	ft_strlcpy(value_out, var_name, ft_strlen(var_name) + 1);
	return (value_out);
}

char	*check_var(t_data *data, char *var_env, char *var_name)
{
	char			*value_out;
	unsigned int	size_var_env;
	unsigned int	size_var_name;

	value_out = NULL;
	size_var_env = chr_strlen(var_env, '=');
	size_var_name = chr_strlen(var_name, '=');
	if (size_var_env != size_var_name)
		return (NULL);
	if (!ft_strncmp(var_env, var_name, size_var_name))
		value_out = get_value(data, var_env + size_var_env + 1);
	return (value_out);
}

char	*var_value(t_data *data, char **env, char *var_name)
{
	unsigned int	idx;
	char			*value_out;

	idx = 0;
	value_out = NULL;
	while (env[idx] != NULL)
	{
		value_out = check_var(data, env[idx], var_name);
		if (value_out != NULL)
			return (value_out);
		idx++;
	}
	return (value_out);
}

char	*mini_getenv(t_data *data, char *var_name)
{
	char	*value;

	if (var_name[0] == '?')
	{
		value = ft_itoa(data->exit_code);
		set_garb_lst(&data->garb_lst, value);
		return (value);
	}
	value = var_value(data, data->tab, var_name);
	return (value);
}

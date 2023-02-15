/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:38:34 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/15 18:25:44 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	g_data;

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
	// set_garb_lst(&g_data.garb_lst, dest);
	return (dest);
}

void	file_dup(int file, int dupnbr)
{
	if (file >= 0)
	{
		dup2(file, dupnbr);
		close(file);
	}
}

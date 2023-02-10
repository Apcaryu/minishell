/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:38:34 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/10 17:22:47 by meshahrv         ###   ########.fr       */
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
	return (dest);
}

void	child_open_utils(t_exec *exec, int fileone, int filezero)
{
	if (fileone == 1)
	{
		dup2(filezero, 0);
		close(filezero);
	}
	else if (exec->infile >= 0)
	{
		dup2(exec->infile, 0);
		close(exec->infile);
	}
}

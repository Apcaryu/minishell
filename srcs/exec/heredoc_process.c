/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:47:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/08 16:48:30 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

void	read_line_heredoc(int fd, t_elem_pars *elem, t_exec *exec)
{
	char	*line;
	char	*limiter;
	int		len_limit;

	limiter = elem->args[0];
	// tmp = elem;
	// count_cmds = 0;
	dprintf(2, "limiter = %s\n", limiter);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		// line = readline("> ");
		len_limit = ft_strlen(limiter);
		
		// dprintf(2, "len_limit = [%s]\n", line);
		if (ft_strnstr(line, limiter, len_limit) && line[len_limit] == '\n')
		{
			// free(line);
			// close(fd);
			break;
			// exit(0);
		}
		write(fd, line, ft_strlen(line));
		// write(fd, "\n", 1);
		// if (!ft_strncmp())
		// dprintf(2, "args[0] = %s\n", elem->args[0]);
		// exit(1);
		// close(fd);
		free(line);
	}
	free(line);
	close(fd);
	// if (exec->nbr_cmd == 0)
	// 	exit (0);
}

int	ft_heredoc(t_elem_pars *elem, t_exec *exec)
{
	int	fd;

	dprintf(2, "args[0] = %s\n", elem->args[0]);
	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	read_line_heredoc(fd, elem, exec);
	fd = open(".here_doc", O_RDONLY, 0644);
	if (fd < 0)
		unlink(".here_doc");
	return (fd);
}

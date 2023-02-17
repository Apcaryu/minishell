/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:47:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 22:14:52 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

extern t_data	g_data;

char	*get_next_lino(int fd)
{
	char	heap[100];
	char	buff;
	int		nbyte;
	int		i;

	i = 0;
	nbyte = read(fd, &buff, 0x1);
	if (fd < 0)
		return (0);
	while (nbyte > 0x0)
	{
		heap[i++] = buff;
		if (buff == '\n')
			break ;
		nbyte = read(fd, &buff, 0x1);
	}
	heap[i] = '\0';
	if (nbyte <= 0 && i == 0)
		return (0);
	return (ft_strdup(heap));
}

void	prompt_eof(t_data *data)
{
	if (data->exit_code == 130)
		dup2(0, data->tmp_fd);
	else
		printf("\nminishell: warning eof\n");
}

void	read_line_heredoc(int fd, t_elem_pars *elem)
{
	char	*line;
	char	*limiter;
	int		len_limit;

	limiter = elem->args[0];
	g_data.tmp_fd = dup(0);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_lino(g_data.tmp_fd);
		if (line == NULL)
		{
			prompt_eof(&g_data);
			break ;
		}
		len_limit = ft_strlen(limiter);
		if (ft_strnstr(line, limiter, len_limit) && line[len_limit] == '\n')
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
}

char	*ft_heredoc(t_elem_pars *elem, int nb_hd)
{
	int		fd;
	char	*here_file;
	char	*nb;
	char	*here_file_joined;

	nb = ft_itoa(nb_hd);
	set_garb_lst(&g_data.garb_lst, nb);
	here_file = "/tmp/.here_doc";
	here_file_joined = ft_strjoin(here_file, nb);
	set_garb_lst(&g_data.garb_lst, here_file_joined);
	fd = open(here_file_joined, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	read_line_heredoc(fd, elem);
	return (here_file_joined);
}

void	open_heredoc(t_elem_pars *elem)
{
	static int		nb_hd = 0;

	g_data.is_heredoc = true;
	while (elem != NULL)
	{
		if (elem->type == HEREDOC)
		{
			elem->args[0] = ft_heredoc(elem, nb_hd);
			elem->type = INFILE;
			nb_hd++;
			if (g_data.exit_code == 130)
				return ;
		}
		elem = elem->next;
	}
	g_data.is_heredoc = false;
}

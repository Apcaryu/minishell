/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:47:04 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/14 13:41:18 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft_42/includes_libft/get_next_line_bonus.h"

extern t_data	g_data;

void	read_line_heredoc(int fd, t_elem_pars *elem)
{
	char	*line;
	char	*limiter;
	int		len_limit;

	limiter = elem->args[0];
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		len_limit = ft_strlen(limiter);
		if (ft_strnstr(line, limiter, len_limit) && line[len_limit] == '\n')
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
}

// void	ft_heredoc(t_elem_pars *elem, int nb_hd)
// {
// 	int		fd;
// 	char	*here_file;
// 	char	*nb;
// 	char	*here_file_joined;

// 	nb = ft_itoa(nb_hd);
// 	here_file = ".here_doc";
// 	here_file_joined = ft_strjoin(here_file, nb);
// 	dprintf(2, "here_file_joined = %s\n", here_file_joined);
// 	fd = open(here_file_joined, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd < 0)
// 		return (NULL);
// 	read_line_heredoc(fd, elem);
// 	// fd = open(".here_doc", O_RDONLY, 0644);
// 	// if (fd < 0)
// 	// 	unlink(".here_doc");
// 	// return (fd);
// }

// void	open_heredoc(t_elem_pars *elem){
// 	static int		nb_hd = 0;
// 	char **args;
	
// 	while (elem != NULL){
// 		if (elem->type == HEREDOC)
// 		{
// 			ft_heredoc(elem, nb_hd);
// 			nb_hd++;
// 		}
// 		elem = elem->next;
// 	}
// }

char*	ft_heredoc(t_elem_pars *elem, int nb_hd)
{
	int		fd;
	char	*here_file;
	char	*nb;
	char	*here_file_joined;

	nb = ft_itoa(nb_hd);
	here_file = "/tmp/.here_doc";
	here_file_joined = ft_strjoin(here_file, nb);
	// set_garb_lst(&g_data.garb_lst, here_file_joined);
	dprintf(2, "here_file_joined = %s\n", here_file_joined);
	fd = open(here_file_joined, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	read_line_heredoc(fd, elem);
	// fd = open(".here_doc", O_RDONLY, 0644);
	// if (fd < 0)
	// 	unlink(".here_doc");
	// return (fd);
	return (here_file_joined);
}

void	open_heredoc(t_elem_pars *elem){
	static int		nb_hd = 0;
	char **args;
	
	while (elem != NULL){
		if (elem->type == HEREDOC)
		{
			elem->args[0] = ft_heredoc(elem, nb_hd);
			elem->type = INFILE;
			nb_hd++;
		}
		elem = elem->next;
	}
}

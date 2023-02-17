/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meshahrv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 07:38:26 by meshahrv          #+#    #+#             */
/*   Updated: 2023/02/16 07:38:29 by meshahrv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft_42/includes_libft/libft.h"
# include "../libft_42/includes_libft/garbage.h"

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef enum e_ntype
{
	NONE,
	INFILE,
	HEREDOC,
	OUTFILE,
	APPEND,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	COMMAND,
	C_SPACE,
	VARIABLE,
	ARGS
}	t_type;

typedef struct s_token
{
	t_type				type;
	char				*content;
	t_bool				is_closed;
	struct s_token		*next;
}	t_token;

typedef struct s_elem_pars
{
	t_type				type;
	char				*cmd;
	char				**args;
	t_bool				is_closed;
	struct s_elem_pars	*next;
}	t_elem_pars;

typedef struct s_lst_pid
{
	pid_t				pid;
	struct s_lst_pid	*next;
}	t_lst_pid;

typedef struct s_exec
{
	t_lst_pid	*pid;
	int			tmp_pid;
	int			pipefd[2];
	int			stdsave[2];
	int			status;
	int			exit_code;
	int			nbr_cmd;
	int			nbr_pipes;
	char		**cmds;
	int			infile;
	int			outfile;
}	t_exec;

typedef struct s_env
{
	char			*line;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char			*input;
	t_list			*garb_lst;
	t_token			*lexer_lst;
	t_elem_pars		*parser_lst;
	t_exec			*exec_struct;
	char			**env;
	t_env			*env_bis;
	char			**tab;
	t_bool			is_interactive;
	t_bool			is_heredoc;
	unsigned char	exit_code;
	int				tmp_fd;
}	t_data;

void	closer(void);
char	**garb_split(char const *s, char c, t_list *garb_lst);

#endif

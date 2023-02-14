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

typedef enum	e_bool
{
	false,
	true
}	t_bool;

typedef enum	e_ntype
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
	char 				*content;
	t_bool 				is_closed;
	struct s_token		*next;
}	t_token;

typedef struct s_elem_pars
{
	t_type			type;
	char			*cmd;
	char			**args;
	t_bool			is_closed;
	struct s_elem_pars	*next;
}	t_elem_pars;

typedef struct s_exec
{
	pid_t	pid;
	int		pipefd[2];
	int		stdsave[2];
	int		status;
	int 	exit_code;
	int		nbr_cmd;
	int		nbr_pipes;
	char	**cmds;
	int		infile;
	int		outfile;
}	t_exec;

// typedef struct s_proc
// {
// 	t_elem_pars *elem_list;
// 	int		infile;
// 	int		outfile;
// 	char * cmd;
// 	char** args;
// 	int		pid[2];
// 	int		pipefd[2];
// 	int		status;
// 	int 	exit_code;

// };

typedef struct	s_env
{
	char			*line;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char 			*input;
	t_list 			*garb_lst;
	t_token			*lexer_lst;
	t_elem_pars		*parser_lst;
	t_exec			*exec_struct;
	char			**env;
	t_env			*env_bis;
	char			**tab;
	t_bool			is_interactive;
	unsigned char	exit_code;
}	t_data;



char	**garb_split(char const *s, char c, t_list *garb_lst);

#endif
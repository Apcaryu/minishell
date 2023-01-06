#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft_42/includes_libft/libft.h"
# include "../libft_42/includes_libft/garbage.h"

typedef enum	e_bool
{
	false,
	true
}	t_bool;

typedef enum	e_type
{
	NONE,
	INFILE,
	HEREDOC,
	OUTFILE,
	APPEND,
	PIPE,
	COMMAND,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
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
	t_type				type;
	char				*cmd;
	char				**args;
	struct s_elem_pars	*next;
}	t_elem_pars;

typedef struct s_exec
{
	int	pid[2];
	int	pipefd[2];
}	t_exec;

typedef struct s_data
{
	char 		*input;
	t_list 		*garb_lst;
	t_token		*lexer_lst;
	t_elem_pars	*parser_lst;
	t_exec		*exec_struct;
	char		**env;
}	t_data;

char	**garb_split(char const *s, char c, t_list *garb_lst);

#endif
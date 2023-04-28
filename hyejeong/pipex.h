#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft.h"

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}				t_bool;

typedef enum e_rw
{
	READ = 0,
	WRITE = 1
}			t_rw;


typedef struct	s_info
{
	int					num_pipe;
	int					**pipes;
	pid_t				*arr_pid;
	char				**envp;
}				t_info;

typedef struct	s_deque
{
	struct s_node	*front;
	struct s_node	*rear;
}				t_deque;

typedef struct	s_node
{
	int				idx;
	int				num_heredoc;
	char			**cmd;
	char			**order_redir;
	char			**file_redir;
	char			**filename_heredoc;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct	s_heredoc
{
	char	**terminators;
	char	**filename_temp;
	int		size_heredoc;
	int		*fd_heredoc;
}				t_heredoc;



#endif
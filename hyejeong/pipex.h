#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../before_sum/sumofshell/libft/mylibft.h"

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

t_deque *new_deque(void);
int deque_size(t_deque *deque);
void    push_r(t_deque *deque, t_node *node);
char    *find_env_path(char **envp);
char    *free_and_return(char **token_env_path, char *buffer);
char    **tokenize(char **envp);
char    *find_command_path(char *cmd, char **envp);
t_bool  exec(char **cmd_args, char **envp);
void    get_heredoc(t_heredoc *hdoc);
void    parsing_heredoc(char **arg, t_heredoc *hdoc);
void    init_t_heredoc(t_heredoc *hdoc);
t_heredoc   *do_heredoc(char **arg, t_deque *deque);
void    cnt_heredoc_in_node(t_deque *deque);
void    distribute_heredoc(t_deque *deque, t_heredoc *hdoc);
int ft_here_doc(t_heredoc *hdoc, int idx);
t_node  *new_node(void);
void    init_node(t_node *node);
t_node  *push_init_new_node(t_deque *deque);
void    redir_infile(t_node *node, int i);
void    redir_outfile_ow(t_node *node, int i);
void    redir_outfile_apd(t_node *node, int i);
void    redir_heredoc(t_node *node, int i, int idx_hd_in_node);
void    unlink_temp_file(t_heredoc *hdoc);
int **create_pipes(int num_pipe);
t_info  *init_info(t_deque *deque);
t_deque *parsing_pipe(char **arg);
void    run_cmd(char **arg, char **envp);
void    check_pipe_redir(t_node *node, t_info *info);
void    check_file_redir(t_node *node, t_info *info);
void    child_process(t_node *node, t_info *info, char **envp);
t_node  *parent_process(t_node *node, t_info *info);
int ft_wait_pids(t_info *info);
void    ft_p_error(char *str);
void    free_2d_array(char **arr);
void    init_2d_arr(char ***arr);
char    **append_str(char **arg, char *str);



#endif
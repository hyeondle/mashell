/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:05:49 by hyeondle          #+#    #+#             */
/*   Updated: 2023/04/29 10:37:24 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "../before_sum/sumofshell/includes/structs.h"

/*			deque			*/
t_deque		*new_deque(void);
int			deque_size(t_deque *deque);
void		push_r(t_deque *deque, t_node *node);

/*			exec			*/
char		*find_env_path(char **envp);
char		*free_and_return(char **token_env_path, char *buffer);
char		**tokenize(char **envp);
char		*find_command_path(char *cmd, char **envp);
t_bool		exec(char **cmd_args, char **envp);

/*			heredoc			*/
void		get_heredoc(t_heredoc *hdoc);
void		parsing_heredoc(char **arg, t_heredoc *hdoc);
void		init_t_heredoc(t_heredoc *hdoc);
t_heredoc	*do_heredoc(char **arg, t_deque *deque);
void		cnt_heredoc_in_node(t_deque *deque);
void		distribute_heredoc(t_deque *deque, t_heredoc *hdoc);
int			ft_here_doc(t_heredoc *hdoc, int idx);

/*			node			*/
t_node		*new_node(void);
void		init_node(t_node *node);
t_node		*push_init_new_node(t_deque *deque);

/*			redir			*/
void		redir_infile(t_node *node, int i);
void		redir_outfile_ow(t_node *node, int i);
void		redir_outfile_apd(t_node *node, int i);
void		redir_heredoc(t_node *node, int i, int idx_hd_in_node);

/*			run				*/
void		unlink_temp_file(t_heredoc *hdoc);
int			**create_pipes(int num_pipe);
t_info		*init_info(t_deque *deque);
t_deque		*parsing_pipe(char **arg);
void		run_cmd(char **arg, char **envp, t_setting **set);
void		check_pipe_redir(t_node *node, t_info *info);
void		check_file_redir(t_node *node, t_info *info);
void		child_process(t_node *node, t_info *info, char **envp);
t_node		*parent_process(t_node *node, t_info *info);
int			ft_wait_pids(t_info *info, t_setting **set);

/*			utils			*/
void		ft_p_error(char *str);
void		free_2d_array(char **arr);
void		init_2d_arr(char ***arr);
char		**append_str(char **arg, char *str);

#endif
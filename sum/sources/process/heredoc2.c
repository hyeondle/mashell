/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejeong <hyejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:05:44 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/05 22:34:13 by hyejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	cnt_heredoc_in_node(t_deque *deque)
{
	t_node	*node;
	int		i;

	node = deque->front;
	while (node)
	{
		i = 0;
		while (node->order_redir[i])
		{
			if (ft_strcmp(node->order_redir[i], "<<") == 0)
				node->num_heredoc++;
			i++;
		}
		node = node->next;
	}
}

void	distribute_heredoc(t_deque *deque, t_heredoc *hdoc)
{
	t_node	*node;
	int		idx_hd;
	int		i;

	idx_hd = 0;
	node = deque->front;
	while (node)
	{
		i = 0;
		while (i < node->num_heredoc)
		{
			node->filename_heredoc = append_str(node->filename_heredoc, \
			hdoc->filename_temp[idx_hd]);
			idx_hd++;
			i++;
		}
		node = node->next;
	}
}

void	signal_handler_for_parent(int sig)
{
	if (sig == SIGINT)
	{
		exit_status = 1;
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler(int sig)
{
	char	*tmp;

	if (sig == SIGINT)
	{
		exit_status = 1;
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		tmp = ft_itoa(exit_status);
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putstr_fd(tmp, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(tmp);
		exit(1);
	}
}

void	ft_signal_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, signal_handler);
}


int	ft_here_doc(t_heredoc *hdoc, int idx)
{
	char	*str;
	pid_t	pid;
	int		here_fd;
	int		status;

	rl_catch_signals = 1;
	here_fd = open(hdoc->filename_temp[idx], O_RDWR | O_CREAT | O_TRUNC, 0666);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		ft_signal_child();
		signal(SIGQUIT, SIG_IGN);
		while (1)
		{
			str = readline("> ");
			if (!str || ft_strcmp(hdoc->terminators[idx], str) == 0)
			{
				if (str)
					free(str);
				exit(0);
			}
			write(here_fd, str, ft_strlen(str));
			write(here_fd, "\n", 1);
			free(str);
		}
	}
	signal(SIGINT, signal_handler_for_parent);
	signal(SIGQUIT, SIG_IGN);
	wait(&status);
	if (WIFSIGNALED(status))
		exit_status = -5;
	return (here_fd);
}

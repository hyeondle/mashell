/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:05:44 by hyeondle          #+#    #+#             */
/*   Updated: 2023/04/29 10:16:55 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	ft_here_doc(t_heredoc *hdoc, int idx)
{
	char	*str;
	pid_t	pid;
	int		here_fd;

	here_fd = open(hdoc->filename_temp[idx], O_RDWR | O_CREAT | O_TRUNC, 0666);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
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
	wait(NULL);
	return (here_fd);
}

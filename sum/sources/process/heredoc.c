/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Linsio <Linsio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:05:43 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/01 23:10:34 by Linsio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	get_heredoc(t_heredoc *hdoc)
{
	int	i;

	hdoc->fd_heredoc = malloc(sizeof(int) * hdoc->size_heredoc);
	i = 0;
	while (i < hdoc->size_heredoc)
	{
		hdoc->fd_heredoc[i] = ft_here_doc(hdoc, i);
		i++;
	}
}

void	parsing_heredoc(char **arg, t_heredoc *hdoc)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], "<<") == 0)
		{
			hdoc->terminators = append_str(hdoc->terminators, arg[i + 1]);
			hdoc->filename_temp = append_str(hdoc->filename_temp, \
			ft_strjoin("./.here_doc", ft_itoa(hdoc->size_heredoc)));
			hdoc->size_heredoc++;
		}
		i++;
	}
}

void	init_t_heredoc(t_heredoc *hdoc)
{
	init_2d_arr(&(hdoc->terminators));
	init_2d_arr(&(hdoc->filename_temp));
	hdoc->size_heredoc = 0;
}

void hd_handler(int sig, siginfo_t *info, void *oldsiga)
{
	if (sig == SIGINT)
		exit(0);
}

void	init_hd_sig(void)
{
	struct sigaction	act;

	rl_catch_signals = 1;
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = hd_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

t_heredoc	*do_heredoc(char **arg, t_deque *deque)
{
	t_heredoc	*hdoc;

	hdoc = malloc(sizeof(t_heredoc) * 1);
	init_t_heredoc(hdoc);
	parsing_heredoc(arg, hdoc);

	init_hd_sig();
	get_heredoc(hdoc);

	cnt_heredoc_in_node(deque);
	distribute_heredoc(deque, hdoc);
	return (hdoc);
}

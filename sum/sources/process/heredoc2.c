/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Linsio <Linsio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:05:44 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/03 08:46:36 by Linsio           ###   ########.fr       */
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
//여기서부터
int	sig1(void)
{
	exit(0);
	return (0);
}
static void	handler(int sig, siginfo_t *info, void *oldsiga)
{
	if (sig == SIGQUIT)
		rl_redisplay();
	else if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
}

void	init_signalaction2(void)
{
	struct sigaction	act;

	rl_catch_signals = 0;
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
// 여기까지 다른데로 옮김
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
		rl_catch_signals = 1; // 이건 sig1함수안에 넣어도 됨
		signal(SIGINT, sig1); // 이걸 .here_doc파일 비우는걸로 제작
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
	init_signalaction2(); // 이건 메인에 있는것과 같음. 그냥 이 함수말고 외부함수에서 한번 더 호출해도 됨
	return (here_fd);
}

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

// //여기서부터
// int	sig1(void)
// {
// 	exit(5);
// 	return (5);
// }
// static void	handler(int sig, siginfo_t *info, void *oldsiga)
// {
// 	if (sig == SIGQUIT)
// 		rl_redisplay();
// 	else if (sig == SIGINT)
// 	{
// 		rl_replace_line("", 1);
// 		rl_on_new_line();
// 		printf("\n");
// 		rl_redisplay();
// 	}
// }

// void	init_signalaction2(void)
// {
// 	struct sigaction	act;

// 	rl_catch_signals = 0;
// 	act.sa_flags = SA_SIGINFO;
// 	act.sa_sigaction = handler;
// 	sigemptyset(&act.sa_mask);
// 	sigaction(SIGINT, &act, NULL);
// 	sigaction(SIGQUIT, &act, NULL);
// }
// // 여기까지 다른데로 옮김
// // int	ft_here_doc(t_heredoc *hdoc, int idx)
// // {
// // 	char	*str;
// // 	pid_t	pid;
// // 	int		here_fd;

// // 	here_fd = open(hdoc->filename_temp[idx], O_RDWR | O_CREAT | O_TRUNC, 0666);
// // 	pid = fork();
// // 	if (pid < 0)
// // 		exit(1);
// // 	if (pid == 0)
// // 	{
// // 		rl_catch_signals = 1; // 이건 sig1함수안에 넣어도 됨
// // 		signal(SIGINT, sig1); // 이걸 .here_doc파일 비우는걸로 제작
// // 		while (1)
// // 		{
// // 			str = readline("> ");
// // 			if (!str || ft_strcmp(hdoc->terminators[idx], str) == 0)
// // 			{
// // 				if (str)
// // 					free(str);
// // 				exit(0);
// // 			}
// // 			write(here_fd, str, ft_strlen(str));
// // 			write(here_fd, "\n", 1);
// // 			free(str);
// // 		}
// // 	}
// // 	wait(NULL);
// // 	init_signalaction2(); // 이건 메인에 있는것과 같음. 그냥 이 함수말고 외부함수에서 한번 더 호출해도 됨
// // 	return (here_fd);
// // }


// // void	handle_execute_exit_status(int status)
// // {
// // 	if (WIFEXITED(status))
// // 		exit_status = WEXITSTATUS(status);
// // 	else if (WIFSIGNALED(status))
// // 		exit_status = WTERMSIG(status) + 128;
// // }


// int	ft_here_doc(t_heredoc *hdoc, int idx)
// {
// 	char	*str;
// 	pid_t	pid;
// 	int		here_fd;
// 	int		status;

// 	// signal(SIGINT, SIG_IGN);
// 	here_fd = open(hdoc->filename_temp[idx], O_RDWR | O_CREAT | O_TRUNC, 0666);
// 	pid = fork();
// 	if (pid < 0)
// 		exit(1);
// 	if (pid == 0)
// 	{
// 		rl_catch_signals = 1; // 이건 sig1함수안에 넣어도 됨
// 		signal(SIGINT, sig1); // 이걸 .here_doc파일 비우는걸로 제작
// 		while (1)
// 		{
// 			str = readline("> ");
// 			if (!str || ft_strcmp(hdoc->terminators[idx], str) == 0)
// 			{
// 				if (str)
// 					free(str);
// 				exit(0);
// 			}
// 			write(here_fd, str, ft_strlen(str));
// 			write(here_fd, "\n", 1);
// 			free(str);
// 		}
// 	}
// 	else
// 	{
// 		signal(SIGINT, handler);
// 		// a = wait(NULL);

// 		wait(&status);
// 		// if (status == 5)
// 		// 	printf("status == 5\n");
// 		// else
// 		// 	printf("status != 5\n");
// 		// printf("status : %d\n", status);
// 		// printf("%d\n", WEXITSTATUS(status));

// 		// init_signalaction2(); // 이건 메인에 있는것과 같음. 그냥 이 함수말고 외부함수에서 한번 더 호출해도 됨
// 		if (WEXITSTATUS(status) == 5)
// 			exit_status = 5;
// 		return (here_fd);

// 	}
// }


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
	{
		printf("\n");
		exit_status = -5;
	}
	printf("%d\n", exit_status);
	return (here_fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:20:20 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/05 23:14:43 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_signal_child(void)
{
	struct sigaction	act;

	rl_catch_signals = 1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	act.sa_flags = SA_SIGINFO;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	ignores(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

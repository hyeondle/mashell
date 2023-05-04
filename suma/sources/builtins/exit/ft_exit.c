/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Linsio <Linsio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 02:49:06 by Linsio            #+#    #+#             */
/*   Updated: 2023/05/04 12:36:33 by Linsio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	digit_check(char *str)
{
	int	i;
	int	k;

	i = 0;
	while (str[i])
	{
		k = ft_isdigit(str[i]);
		if (k == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	exit_with_input(char **inputs, t_setting **set)
{
	int	i;

	if (inputs[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDOUT_FILENO);
		(*set)->exit = 0;
		(*set)->last_exit_status = 1;
	}
	else
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		i = digit_check(inputs[1]);
		if (i)
		{
			printf("exit: %s: numeric argument required\n", inputs[1]);
			(*set)->last_exit_status = 255;
		}
		else
			(*set)->last_exit_status = (ft_atoi(inputs[1]) % 256);
	}
}

int	ft_exit(char **inputs, t_setting **set)
{
	(*set)->exit = 1;
	if (inputs[1])
		exit_with_input(inputs, set);
	else
	{
		(*set)->last_exit_status = 0;
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 02:49:06 by Linsio            #+#    #+#             */
/*   Updated: 2023/04/29 09:05:39 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_exit(char **inputs, t_setting **set)
{
	(*set)->exit = 1;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	return (0);
}

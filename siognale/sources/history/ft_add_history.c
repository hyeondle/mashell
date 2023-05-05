/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 03:57:58 by hyeondle          #+#    #+#             */
/*   Updated: 2023/04/29 08:57:40 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_history(char *input, t_setting **set)
{
	t_history	*hist;
	t_history	*temp;
	char		*str;

	add_history(input);
	hist = (t_history *)malloc(sizeof(t_history));
	if (!hist)
		return ;
	str = ft_strdup(input);
	if (!str)
		return ;
	hist->history = str;
	hist->next = NULL;
	if ((*set)->s_history == NULL)
		(*set)->s_history = hist;
	else
	{
		temp = ((*set)->s_history);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = hist;
	}
}

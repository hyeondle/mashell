/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 08:46:30 by hyeondle          #+#    #+#             */
/*   Updated: 2023/04/08 08:46:50 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

size_t	tab_size(char *s)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (s[k] == ' ')
		if (s[k + 1] != ' ')
			k++;
	while (s[k])
	{
		if (s[k] == ' ')
		{
			while (s[k + 1] == ' ' && s[k + 1] != '\0')
				k++;
			if (s[k + 1] != '\0' && s[k + 1] != ' ')
				i++;
		}
		else if (s[k] == '\'' || s[k] == '\"')
		{
			k = quote_leng(s, k);
			i++;
		}
		k++;
	}
	return (i + 1);
}

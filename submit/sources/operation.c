/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:03:12 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/06 09:03:03 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	operation(char *input, t_setting **set)
{
	char	*temp;
	char	**tokenized_str;
	char	**joined_str;
	int		i;

	i = 0;
	temp = convertion(set, input);
	joined_str = shell_split(temp);
	tokenized_str = split_by_token(joined_str);
	i = 0;
	while (tokenized_str[i])
	{
		tokenized_str[i] = del_quotes(set, tokenized_str[i]);
		i++;
	}
	execute(tokenized_str, set);
	free_tab(tokenized_str);
}

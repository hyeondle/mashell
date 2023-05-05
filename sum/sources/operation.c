/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejeong <hyejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:03:12 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/05 22:46:48 by hyejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	operation(char *input, t_setting **set)
{
	char	**tokenized_str;
	char	**joined_str;
	int		i;

	i = 0;
	input = convertion(set, input);
	tokenized_str = shell_split(input);
	tokenized_str = split_by_token(tokenized_str);
	i = 0;
	while (tokenized_str[i])
	{
		tokenized_str[i] = del_quotes(set, tokenized_str[i]);
		i++;
	}
	execute(tokenized_str, set);
}

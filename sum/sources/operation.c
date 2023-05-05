/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:03:12 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/05 19:47:49 by hyeondle         ###   ########.fr       */
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

/*
void	operation(char *input, t_setting **set)
{
	char	**tokenized_str;
	char	**joined_str;
	int		i;

	i = 0;
	// tokenized_str = shell_split(input);
	// tokenized_str = split_by_token(tokenized_str);
	// while (tokenized_str[i])
	// {
	// 	tokenized_str[i] = convertion(set, tokenized_str[i]);
	// 	i++;
	// }
	// i = 0;
	// while (tokenized_str[i])
	// {
	// 	tokenized_str[i] = del_quotes(set, tokenized_str[i]);
	// 	i++;
	// }
	input = convertion(set, input);
	tokenized_str = shell_split(input);
	tokenized_str = split_by_token(tokenized_str);
	// i = 0;
	// while (tokenized_str[i])
	// {
	// 	tokenized_str[i] = convertion(set, tokenized_str[i]);
	// 	i++;
	// }
	i = 0;
	while (tokenized_str[i])
	{
		tokenized_str[i] = del_quotes(set, tokenized_str[i]);
		i++;
	}
	execute(tokenized_str, set);
	// while (tokenized_str[i])
	// {
	// 	printf("%d : %s%c\n", i, tokenized_str[i], '$');
	// 	i++;
	// }
}
*/
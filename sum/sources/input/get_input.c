/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Linsio <Linsio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 01:33:48 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/03 13:01:41 by Linsio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	forced_terminated(char *input, char *input_p)
{
	int i = 0;
	if (!input)
	{
		printf("unexpected EOF while looking for matching `\n");
		printf("syntax error: unexpected end of file\n");
		free(input);
		input = NULL;
		return (0);
	}
	return (1);
}

char	*join_input(char *input, char *input_add)
{
	char	*temp;

	temp = input;
	input = ft_strjoin(input, input_add);
	input = check_input_add(input);
	free(input_add);
	free(temp);
	return (input);
}

char	*get_input(t_setting **set)
{
	char	*input;
	char	*input_add;
	int		i;

	input = readline("minishell> ");
	if (!input)
		exit(0);
	i = input_check(input);
	if (i == 1)
	{
		printf("syntax error: unexpected end of file\n");
		// input = ft_strjoin(input, "\n");
		// while (i)
		// {
		// 	input_add = readline("> ");
		// 	if (!input_add)
		// 	{
		// 		i = forced_terminated(input_add, input);
		// 		if (i == 0)
		// 			break;
		// 	}
		// 	input = join_input(input, input_add);
		// 	i = input_check(input);
		// }
	}
	return (input);
}

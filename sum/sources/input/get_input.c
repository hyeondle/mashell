/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Linsio <Linsio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 01:33:48 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/02 10:06:24 by Linsio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//get whole input
#include "../../includes/minishell.h"

t_bool	forced_terminated(char *input)
{
	// 여기서 따옴표 닫히지 않은채로 종료된 것이 확인 될 경우 에러메시지를 출력하도록 설정
	// 그 후 어떻게 종료되는지 확인할 것. "ctrl+d"로 인한 EOF가 들어올 경우 에러가남
}

char	*get_input(t_setting **set)
{
	char	*input;
	char	*input_add;
	int		i;

	input = readline("minishell> ");
	if (!input)
		ft_exit(NULL, set);
	i = input_check(input);
	if (i == 1)
	{
		input = ft_strjoin(input, "\n");
		while (i)
		{
			input_add = readline("> ");
			if (!input_add)
				break ;
			input_add = check_input_add(input_add);
			input = ft_strjoin(input, input_add);
			free(input_add);
			i = input_check(input);
		}
	}
	return (input);
}

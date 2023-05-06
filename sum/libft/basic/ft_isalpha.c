/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:20:14 by hyeondle          #+#    #+#             */
/*   Updated: 2023/05/06 04:12:22 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int num)
{
	if ((num > 64 && num < 91) || (num > 64 + 32 && num < 91 + 32))
		return (1);
	else if (num == 95)
		return (1);
	else
		return (0);
}

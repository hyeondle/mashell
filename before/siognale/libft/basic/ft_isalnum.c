/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:23:15 by hyeondle          #+#    #+#             */
/*   Updated: 2022/07/15 16:54:28 by hyeondle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int num)
{
	if ((num > 64 && num < 91) || (num > 64 + 32 && num < 91 + 32))
		return (1);
	else if (num > 47 && num < 58)
		return (1);
	else
		return (0);
}
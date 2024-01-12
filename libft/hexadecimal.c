/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexadecimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:05:07 by xortega           #+#    #+#             */
/*   Updated: 2024/01/12 14:40:52 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	print_hex(va_list lst, char c)
{
	unsigned int	num;
	unsigned int	base;
	unsigned int	out;
	unsigned int	count;

	count = 0;
	base = 1;
	num = va_arg(lst, unsigned int);
	while (++count && (num / base) >= 16)
		base *= 16;
	out = count;
	while (count-- >= 1)
	{
		if ((num / base) <= 9)
			ft_putchar_fd(((num / base) + 48), 1);
		else if (c == 'X')
			ft_putchar_fd(((num / base) + 55), 1);
		else
			ft_putchar_fd(((num / base) + 87), 1);
		num %= base;
		base /= 16;
	}
	return (out);
}

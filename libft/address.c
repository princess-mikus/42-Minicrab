/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:05:07 by xortega           #+#    #+#             */
/*   Updated: 2024/04/03 12:44:02 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex(unsigned long num)
{
	unsigned long	base;
	int				out;
	int				count;

	count = 0;
	base = 1;
	while (++count && (num / base) >= 16)
		base *= 16;
	out = count;
	while (count-- >= 1)
	{
		if ((num / base) <= 9)
			ft_putchar_fd(((num / base) + 48), 1);
		else
			ft_putchar_fd(((num / base) + 87), 1);
		num %= base;
		base /= 16;
	}
	return (out);
}

int	print_addres(va_list lst)
{
	unsigned long	add;
	void			*ptr;

	ptr = va_arg(lst, void *);
	add = (unsigned long)ptr;
	write(1, "0x", 2);
	return (hex(add) + 2);
}

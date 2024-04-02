/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:05:07 by xortega           #+#    #+#             */
/*   Updated: 2024/01/24 14:24:01 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	sizefb(unsigned int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	un_magnitude(unsigned int n)
{
	unsigned int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i *= 10;
	}
	return (i);
}

static void	ft_un_putnbr_fd(unsigned int n, int fd)
{
	unsigned int	mag;
	unsigned int	size;
	char			c;

	size = sizefb(n);
	mag = un_magnitude(n);
	while (size > 0)
	{
		c = ((n / mag) + 48);
		write(fd, &c, 1);
		n %= mag;
		mag /= 10;
		size--;
	}
}

int	print_unsigned(va_list lst)
{
	int	number;

	number = va_arg(lst, unsigned int);
	ft_un_putnbr_fd(number, 1);
	return (sizefb(number));
}

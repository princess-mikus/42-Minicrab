/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:05:07 by xortega           #+#    #+#             */
/*   Updated: 2024/01/12 14:39:38 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	au_magnitude(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i += 1;
	}
	return (i);
}

int	print_number(va_list lst)
{
	int	number;

	number = va_arg(lst, int);
	if (number == -2147483648)
		return (write(1, "-2147483648", 11));
	ft_putnbr_fd(number, 1);
	return (au_magnitude(number));
}

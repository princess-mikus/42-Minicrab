/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:23:42 by xortega           #+#    #+#             */
/*   Updated: 2024/04/03 12:44:02 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	magnitude(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		n *= -1;
	while (n > 9)
	{
		n /= 10;
		i *= 10;
	}
	return (i);
}

static int	size(int n)
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

char	*ft_itoa(int n)
{
	char	*dst;
	int		mag;
	int		i;

	i = 0;
	mag = magnitude(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	dst = malloc((size(n) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	if (n < 0)
	{
		dst[i++] = '-';
		n *= -1;
	}
	while (mag > 0)
	{
		dst[i] = ((n / mag) + 48);
		n %= mag;
		mag /= 10;
		i++;
	}
	dst[i] = 0;
	return (dst);
}

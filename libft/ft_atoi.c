/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:56:50 by xortega           #+#    #+#             */
/*   Updated: 2024/04/03 12:44:02 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_minus(const char *s, int x)
{
	if (s[x] == '-' && (s[x + 1] >= '0' && s[x + 1] <= '9'))
		return (-1);
	if (s[x] == '+' && (s[x + 1] >= '0' && s[x + 1] <= '9'))
		return (1);
	if ((s[x] < '0' || s[x] > '9'))
		return (0);
	if (s[0] == '0' && s[1] == ' ')
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	j;
	int	c;
	int	x;

	x = 0;
	j = -1;
	c = 0;
	while ((str[++j] <= '\0' && str[j] >= '\10') || str[j] == ' ' || \
	str[j] == '\t' || str[j] == '\n' || str[j] == '\v' || \
	str[j] == '\f' || str[j] == '\r')
		x++;
	while (str[j])
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			if (str[j + 1] >= '0' && str[j + 1] <= '9')
				c = (c * 10) + ((str[j] - 48) * 10);
			else
				c += (str[j] - 48);
		}
		if ((str[j + 1] > '9' || str[j + 1] < '0') && c != 0)
			break ;
		j++;
	}
	return (c * ft_minus(str, x));
}

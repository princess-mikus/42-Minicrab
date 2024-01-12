/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:13:29 by xortega           #+#    #+#             */
/*   Updated: 2024/01/12 14:40:52 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	unsigned const char	*source;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	i = -1;
	dest = dst;
	source = src;
	if (dest >= source)
		while (n--)
			dest[n] = source[n];
	else
		while (++i < n)
			(dest[i] = source[i]);
	return (dst);
}

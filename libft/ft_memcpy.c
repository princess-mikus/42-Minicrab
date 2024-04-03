/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:11:55 by xortega           #+#    #+#             */
/*   Updated: 2024/04/03 12:44:02 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	j;

	if (!dst && !src)
		return (NULL);
	j = -1;
	while (++j < n)
		((char *)dst)[j] = ((char *)src)[j];
	return (dst);
}

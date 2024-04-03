/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:18:46 by xortega           #+#    #+#             */
/*   Updated: 2024/04/03 12:44:02 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	source_size;
	size_t	dst_size;

	source_size = ft_strlen(src);
	dst_size = ft_strlen(dst);
	j = -1;
	if (dstsize <= dst_size)
		return (source_size + dstsize);
	while ((++j < (dstsize - dst_size - 1) && src[j]))
		dst[dst_size + j] = src[j];
	dst[dst_size + j] = '\0';
	return (dst_size + source_size);
}

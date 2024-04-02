/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:55:59 by xortega           #+#    #+#             */
/*   Updated: 2024/01/24 14:24:01 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	ns;

	if (len == 0 && (!haystack || !needle))
		return (NULL);
	ns = ft_strlen(needle);
	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return (&((char *)haystack)[i]);
	if (len <= 0)
		return (NULL);
	while (haystack[i] && i < len && len >= (i + ns))
	{
		if (haystack[i] == needle[0] && (ft_strlen(haystack) - i) >= ns)
			if (ft_strncmp(haystack + i, needle, ns) == 0)
				return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:59:25 by xortega           #+#    #+#             */
/*   Updated: 2024/01/24 14:24:01 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	flen;
	size_t	slen;

	if (!s1 || !s2)
		return (NULL);
	flen = ft_strlen(s1) + 1;
	slen = ft_strlen(s2);
	dst = malloc((slen + flen) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, flen);
	ft_strlcat(dst, s2, (slen + flen));
	return (dst);
}

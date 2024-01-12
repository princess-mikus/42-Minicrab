/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:21:51 by xortega           #+#    #+#             */
/*   Updated: 2024/01/12 14:40:52 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	if ((unsigned char)c == '\0')
		return (&((char *)s)[ft_strlen(s)]);
	while (s[++i])
		if (s[i] == ((unsigned char)c) && s[i])
			return (&((char *)s)[i]);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:48:33 by xortega           #+#    #+#             */
/*   Updated: 2024/04/03 12:44:02 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1 || s1 == '\0')
			return (1);
		i++;
	}
	return (0);
}

static size_t	trim_search(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (check(s1[i], set) == 1)
			i++;
		else
			break ;
	}
	return (i);
}

static size_t	trim_rsearch(char const *s1, char const *set)
{
	size_t	size;

	size = ft_strlen(s1);
	while (size > 0)
	{
		if (check(s1[size], set) == 1)
			size--;
		else
			break ;
	}
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	s;
	size_t	rs;

	if (!s1 || !set)
		return (NULL);
	s = trim_search(s1, set);
	rs = trim_rsearch(s1, set);
	if (rs == 0 || s == ft_strlen(s1))
		dst = malloc(1);
	else if (set[0] == '\0')
		dst = malloc(((rs - s) + 1) * sizeof(char));
	else
		dst = malloc(((rs - s) + 2) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, (s1 + s), (rs - s) + 2);
	return (dst);
}

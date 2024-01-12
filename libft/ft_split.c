/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:40:56 by xortega           #+#    #+#             */
/*   Updated: 2024/01/12 14:44:42 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count(char const *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	if (s[i] == '\0')
		return (0);
	if (c == '\0')
		k--;
	while (s[i])
	{
		if (s[i] != c && s[i + 1] == c)
			k++;
		i++;
	}
	if (s[i - 1] == c)
		k--;
	return (k);
}

static int	locate(char const *s, char c, int a)
{
	int	i;

	i = a;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static int	omit(char const *s, char c, int a)
{
	int	i;

	i = a;
	while (s[i])
	{
		if (s[i] != c)
			return (i);
		i++;
	}
	return (i);
}

static char	**del(int k, char **dst)
{
	while (--k >= 0)
		free(dst[k]);
	free(dst);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		l;
	int		k;
	int		a;
	int		i;

	if (!s)
		return (NULL);
	k = 0;
	l = count(s, c);
	dst = malloc((l + 1) * sizeof(char *));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (l-- > 0 && !(c == '\0' && s[0] == '\0'))
	{
		a = omit(s, c, i);
		i = locate(s, c, a);
		dst[k] = ft_substr(s, a, (i - a));
		if (dst[k++] == NULL)
			return (del(k, dst));
	}
	dst[count(s, c)] = NULL;
	return (dst);
}

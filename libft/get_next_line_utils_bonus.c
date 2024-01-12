/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:15:18 by xortega           #+#    #+#             */
/*   Updated: 2024/01/12 14:40:52 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	gnl_strlen(const char *str)
{
	int	c;

	if (!str)
		return (0);
	c = 0;
	while (str[c])
		c++;
	return (c);
}

void	cpy(char *src, char **dst, int start)
{
	int		k;

	k = 0;
	while (src[k] != '\0')
	{
		dst[0][start] = src[k];
		start++;
		k++;
	}
	dst[0][start] = '\0';
}

void	forget(t_struct *all, int fd)
{
	if (!all->temp)
	{
		free(all->rest[fd]);
		all->rest[fd] = NULL;
	}
	else
	{
		free(all->temp);
		all->temp = NULL;
	}
	free(all->buff);
	all->buff = NULL;
}

int	search(t_struct *all)
{
	int	k;

	if (!all->temp || all->temp[0] == '\0')
		return (-1);
	k = 0;
	while (all->temp[k] != '\0')
	{
		if (all->temp[k] == '\n')
			return (++k);
		k++;
	}
	if (all->rd == 0)
		return (-1);
	return (-2);
}

char	*shorter(t_struct *all, int sh, int fd)
{
	char	*dst;
	int		k;

	if (all->rd < 0)
		return (forget(all, fd), NULL);
	if (sh >= 0)
	{
		cut(all, sh, fd);
		dst = pack(all, sh);
		return (forget(all, fd), dst);
	}
	else
	{
		if (!all->temp || all->temp[0] == '\0')
			return (forget(all, fd), NULL);
		k = -1;
		dst = malloc(sizeof(char) * (gnl_strlen(all->temp) + 1));
		if (!dst)
			return (forget(all, fd), NULL);
		while (all->temp[++k])
			dst[k] = all->temp[k];
		dst[k] = '\0';
		return (forget(all, fd), dst);
	}
	return (forget(all, fd), dst);
}

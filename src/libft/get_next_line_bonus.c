/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:53:35 by xortega           #+#    #+#             */
/*   Updated: 2024/01/24 14:24:01 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

void	addnew(t_struct *all, int fd)
{
	char	*after;
	int		before_len;

	before_len = gnl_strlen(all->temp);
	after = malloc(sizeof(char) * (before_len + BUFFER_SIZE + 1));
	if (!after)
	{
		free(all->temp);
		all->temp = NULL;
		all->rd = -1;
		return ;
	}
	all->rd = read(fd, all->buff, BUFFER_SIZE);
	if (all->rd == -1)
		return ;
	all->buff[all->rd] = '\0';
	cpy(all->temp, &after, 0);
	cpy(all->buff, &after, before_len);
	free(all->temp);
	all->temp = NULL;
	all->temp = after;
}

void	remember(t_struct *all, int fd)
{
	int	rest_len;

	rest_len = gnl_strlen(all->rest[fd]);
	all->temp = malloc(sizeof(char) * (rest_len + BUFFER_SIZE + 1));
	if (!all->temp)
		return ;
	all->rd = read(fd, all->buff, BUFFER_SIZE);
	if (all->rd == -1)
	{
		free(all->temp);
		all->temp = NULL;
		return ;
	}
	all->buff[all->rd] = '\0';
	cpy(all->rest[fd], &all->temp, 0);
	cpy(all->buff, &all->temp, rest_len);
	free(all->rest[fd]);
	all->rest[fd] = NULL;
}

void	cut(t_struct *all, int sh, int fd)
{
	int		k;

	k = 0;
	all->rest[fd] = malloc (sizeof(char) * (gnl_strlen(all->temp) - sh + 1));
	if (!all->rest[fd])
		return ;
	while (all->temp[sh])
	{
		all->rest[fd][k] = all->temp[sh];
		k++;
		sh++;
	}
	all->rest[fd][k] = '\0';
}

char	*pack(t_struct *all, int sh)
{
	char	*dst;
	int		k;

	k = 0;
	dst = malloc (sizeof(char) * (sh + 1));
	if (!dst)
	{
		free(all->temp);
		all->temp = NULL;
		return (NULL);
	}
	while (k < sh)
	{
		dst[k] = all->temp[k];
		k++;
	}
	dst[k] = '\0';
	return (dst);
}

char	*get_next_line(int fd)
{
	static t_struct	all = {NULL, NULL, {NULL}, 1};
	int				sh;

	if (fd < 0)
		return (NULL);
	if (all.rest[fd] == NULL)
	{
		all.rest[fd] = malloc(sizeof(char) * 1);
		if (!all.rest[fd])
			return (forget(&all, fd), NULL);
		all.rest[fd][0] = '\0';
	}
	all.buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!all.buff)
		return (forget(&all, fd), NULL);
	remember(&all, fd);
	sh = search(&all);
	while (all.rd > 0 && sh <= 0 && all.temp)
	{
		addnew(&all, fd);
		if (all.temp && all.rd >= 0)
			sh = search(&all);
	}
	return (shorter(&all, sh, fd));
}

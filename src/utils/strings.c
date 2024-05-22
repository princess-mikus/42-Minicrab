/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:23:14 by codespace         #+#    #+#             */
/*   Updated: 2024/05/22 14:06:00 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*jmp_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (str + i);
		i++;
	}
	return (NULL);
}

int	count_out_quotes(char *line, char c)
{
	int	i;
	int	n;
	int	status;

	i = 0;
	status = 0;
	n = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			status++;
		if (line[i] == c && status % 2 == 0)
			n++;
		i++;
	}
	return (n);
}
int	c_out_q_no_d(char *line, char c)
{
	int	i;
	int	n;
	int	status;

	i = 0;
	status = 0;
	n = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			status++;
		if (line[i] == c && status % 2 == 0
		&& line[i + 1] && line[i + 1] != c)
			n++;
		i++;
	}
	return (n);
}

char	*search_out_quotes(char *line, char c)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			status++;
		if (line[i] == c && status % 2 == 0)
			return (line + i);
		i++;
	}
	return (NULL);
}

char	*line_cutter(char *line, char *to_cut)
{
	char	*new_line;
	char	*part_1;
	char	*part_2;
	int		start;
	int		end;

	if (to_cut && line)
	{
		start = ft_strnstr(line, to_cut, ft_strlen(line)) - line;
		end = ft_strlen(to_cut);
		part_1 = ft_substr(line, 0, start);
		part_2 = ft_substr(line, start + end, ft_strlen(line) - (end + start));
		new_line = ft_strjoin(part_1, part_2);
		free(line);
		free(part_1);
		free(part_2);
		return (new_line);
	}
	return (line);
}

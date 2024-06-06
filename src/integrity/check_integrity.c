/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_integrity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:47:36 by mikus             #+#    #+#             */
/*   Updated: 2024/06/06 13:30:02 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_empty_pipe(char *str, int i)
{
	int j;
	static int k = 0;

	j = i - 1;
	k++;
	while (j > 0 && str[j] == ' ')
		j--;
	if (j == 0)
		return (false);
	i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '|')
		return (false);
	return (true);
}

bool	check_infiles(char *str, char c, int *i)
{
	int	j;

	j = 1;
	if (str[j] == c)
	{
		j++;
		*i += 1;
	}
	while (str[j] && str[j] == ' ')
		j++;
	if (!str[j] || str[j] == '|' || str[j] == '>' || str[j] == '<')
		return (false);
	return (true);
}

bool	check_integrity(char *line)
{
	bool	d_quotes;
	bool	s_quotes;
	bool	ret;
	int		i;

	i = 0;
	d_quotes = false;
	s_quotes = false;
	ret = true;
	while (line[i] && ret)
	{
		if (line[i] == '"' && !s_quotes)
			d_quotes ^= 1;
		if (line[i] == '\'' && !d_quotes)
			s_quotes ^= 1;
		if (!d_quotes && !s_quotes && (line[i] == '<' || line[i] == '>'))
			ret = check_infiles(line + i, line[i], &i);
		if (!d_quotes && !s_quotes && (line[i] == '|'))
			ret = check_empty_pipe(line, i);
		i++;
	}
	if (ret && (s_quotes || d_quotes))
		return (false);
	return (ret);
}

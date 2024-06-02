/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_mx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:30:15 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/06/02 16:32:57 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_flag(char *arguments, int *j, bool nl)
{
	if (!arguments)
		return (true);
	while (arguments[*j] == ' ')
		*j += 1;
	if (arguments[*j] == '-' && arguments[*j + 1] == 'n')
	{
		*j += 2;
		while (arguments[*j] == ' ')
			*j += 1;
		return (false);
	}
	if (nl)
		return (true);
	return (false);
}

int	echo_mx(char **arguments)
{
	int		i;
	int		j;
	bool	nl;

	i = 0;
	nl = true;
	while (arguments && arguments[i])
	{
		j = 0;
		nl = get_flag(arguments[i], &j, nl);
		while (arguments[i][j])
		{
			if (write(1, &arguments[i][j], 1) != 1)
				return (1);
			j++;
		}
		if (arguments[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}

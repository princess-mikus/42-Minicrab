/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_mx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:30:15 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/06/07 12:27:44 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_flag(char **arguments, int *i)
{
	bool	nl;

	nl = true;
	if (!arguments)
		return (true);
	while (arguments[*i])
	{
		if (arguments[*i][0] == '-' && arguments[*i][1] == 'n')
		{
			nl = false;
			if (arguments[*i][2])
				break;
			(*i)++;
		}
		else
			break ;
	}
	return (nl);
}

int	echo_mx(char **arguments)
{
	int		i;
	int		j;
	bool	nl;

	i = 0;
	i = 0;
	nl = get_flag(arguments, &i);
	while (arguments && arguments[i])
	{
		j = 0;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_mx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:30:15 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/06/01 14:27:35 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_flag(char *arguments, int *i, bool nl)
{
	if (!arguments)
		return (true);
	while (arguments[*i] == ' ')
		*i += 1;
	if (arguments[*i] == '-' && arguments[*i + 1] == 'n')
	{
		*i += 2;
		while (arguments[*i] == ' ')
			*i += 1;
		return (false);
	}
	*i = 0;
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
		while (arguments[i][j])
		{
			nl = get_flag(arguments[i], &j, nl);
			if (write(1, &arguments[i][j], 1) != 1)
				return (1);
			j++;
		}
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}

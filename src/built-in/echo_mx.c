/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_mx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:30:15 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/05/12 21:29:32 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_flag(char *arguments, int *i)
{
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
	return (true);
}

int	echo_mx(char *arguments)
{
	int		i;
	bool	nl;

	i = 0;
	nl = get_flag(arguments, &i);
	while (arguments[i])
	{
		if (write(1, &arguments[i], 1) != 1)
			return (1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
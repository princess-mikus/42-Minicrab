/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:45:17 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/01/12 15:07:29 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	echo(char **arguments)
{
	int	i;
	int	newline;
	int	len;

	if (!ft_strncmp(arguments[0], "-n", ft_strlen(arguments[0])))
	{
		newline = 0;
		i = 0;
	}
	else
	{
		newline = 1;
		i = -1;
	}
	len = 0;
	while (arguments[len])
		len++;
	while (++i < len)
		ft_putstr_fd(arguments[i], 1);
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

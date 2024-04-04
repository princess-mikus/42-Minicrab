/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:50 by xortega           #+#    #+#             */
/*   Updated: 2024/04/04 11:32:26 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	placeholder();
	while (!ft_strnstr(str, "exit", ft_strlen(str)))
	{
		str = readline("🦀\e[0;93mminicrab: \e[0;37m");
		ft_printf("has escrito: %s\n", str);
		free(str);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:50 by xortega           #+#    #+#             */
/*   Updated: 2024/04/08 11:39:47 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[])
{
	char	*str;

	//ft_initialize();
	argv = NULL;
	argc = 0;
	while (!ft_strnstr(str, "exit", ft_strlen(str)))
	{
		str = readline("🦀\e[0;93mminicrab: \e[0;37m");
			// PARSING_AND_EXECUTION
				// PARSING

				// END PARSING
				// EXECUTION
	
				// END EXECUTION
			// END PARSING AND EXECUTION
		free(str);
	}
	return (0);
}

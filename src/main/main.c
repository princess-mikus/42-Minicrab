/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:50 by xortega           #+#    #+#             */
/*   Updated: 2024/04/08 23:39:20 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	//ft_initialize();
	str = "";
	while (str && !ft_strnstr(str, "exit", ft_strlen(str)))
	{
		str = readline("🦀\e[0;93mminicrab: \e[0;37m");
		add_history(str);
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

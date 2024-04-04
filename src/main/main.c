/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:50 by xortega           #+#    #+#             */
/*   Updated: 2024/04/04 14:09:53 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_imput(void)
{
	char	*str;

	str = readline("🦀\e[0;93mminicrab: \e[0;37m");
	ft_printf("has escrito: %s\n", str);
	return (str);
}

int	main(int argc, char const *argv[], char **envp)
{
	char	*str;
	

	//ft_initialize();
	while (!ft_strnstr(str, "exit", ft_strlen(str)))
	{
		str = read_imput();
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

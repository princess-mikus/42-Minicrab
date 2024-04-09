/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:50 by xortega           #+#    #+#             */
/*   Updated: 2024/04/09 12:55:47 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_envp	*envp_mx;

	init_envp(&envp_mx, envp);
	str = "";
	while ((str && argc && argv) && !ft_strnstr(str, "exit", ft_strlen(str)))
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

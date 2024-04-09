/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:50 by xortega           #+#    #+#             */
/*   Updated: 2024/04/09 13:44:27 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_input input;
	t_envp	*envp_mx;

	envp_mx = NULL;
	init_envp(&envp_mx, envp);
	input.line = "";
	if (argc == 0 || !argv[0])
		return (0);
	while (input.line && !ft_strnstr(input.line, "exit", ft_strlen(input.line)))
	{
		input.line = readline("🦀\e[0;93mminicrab: \e[0;37m");
		add_history(input.line);
		// PARSING_AND_EXECUTION
			// PARSING
		parse_commands(&input, envp_mx);
			// END PARSING
			// EXECUTION
	
				// END EXECUTION
			// END PARSING AND EXECUTION
		free(input.line);
	}
	return (0);
}

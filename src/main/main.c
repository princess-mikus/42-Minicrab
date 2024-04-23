/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:50 by xortega           #+#    #+#             */
/*   Updated: 2024/04/23 14:08:53 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	main(int argc, char **argv, char **envp)
{
	t_input	input;
	t_envp	*envp_mx;

	envp_mx = NULL;
	init_envp(&envp_mx, envp);
	input.line = ft_strdup("");
	if (argc == 0 || !argv[0] || !envp)
		return (0);
	while (input.line)
	{
		free(input.line);
		input.line = readline("🦀\e[0;93mminicrab: \e[0;37m");
		if (!ft_strncmp(input.line, "exit", 5))
			break ;
		if (input.line[0])
			add_history(input.line);
		parse_commands(&input, envp_mx);
		//rl_on_new_line();
	}
	free_envp_mx(&envp_mx);
	//clear_history();
	return (0);
} */

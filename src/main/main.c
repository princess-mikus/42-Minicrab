/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:50 by xortega           #+#    #+#             */
/*   Updated: 2024/05/06 13:38:47 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_envp		*envp_mx;

	envp_mx = NULL;
	init_envp(&envp_mx, envp);
	line = ft_strdup("");
	if (argc == 0 || !argv[0] || !envp)
		return (0);
	while (line)
	{
		free(line);
		line = readline("🦀\e[0;93mminicrab: \e[0;37m");
		if (!ft_strncmp(line, "exit", 5))
			break ;
		if (line[0])
			add_history(line);
		parse_commands(line, envp_mx);
		//rl_on_new_line();
	}
	free_envp_mx(&envp_mx);
	//clear_history();
	return (0);
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:49:25 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/06/02 16:45:14 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean(t_command **commands)
{
	t_command *current;

	current = *commands;
	while (current)
	{
		cleaning(current);
		current = current->next;
	}
}

void	parse_commands(char *line, t_envp **envp_mx)
{
	char		*line_expanded;
	t_command	*commands;

	commands = NULL;
	line_expanded = expansion(envp_mx, line);
	free(line);
	if (line_expanded[0])
	{
		parse(line_expanded, &commands);
		clean(&commands);
		execute_commands(&commands, envp_mx);
		free_command_list(&commands);
	}
	free(line_expanded);
}

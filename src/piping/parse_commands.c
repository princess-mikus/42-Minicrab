/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:49:25 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/05/10 15:26:55 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_commands(char *line, t_envp *envp_mx)
{
	char		*line_expanded;
	t_command	*commands;

	commands = NULL;
	line_expanded = expansion(&envp_mx, line);
	parse(line_expanded, &commands);
	execute_commands(&commands, envp_mx);
	free(line_expanded);
	free_command_list(&commands);
}

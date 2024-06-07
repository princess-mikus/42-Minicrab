/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:49:25 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/06/07 13:58:51 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean(t_command **commands)
{
	t_command	*current;

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
	if (!check_integrity(line))
	{
		ft_putstr_fd("minicrab: syntax error near unexpected token\n", 2);
		add_var_to_envp_mx(envp_mx, "?", ft_strdup("2"));
		return ;
	}
	line_expanded = expansion(envp_mx, line);
	if (line_expanded[0])
	{
		parse(line_expanded, &commands);
		clean(&commands);
		if (!commands->command && commands->dec && !commands->next)
			dec_to_env(commands->dec, envp_mx);
		else
			execute_commands(&commands, envp_mx);
		free_command_list(&commands);
	}
	free(line_expanded);
}

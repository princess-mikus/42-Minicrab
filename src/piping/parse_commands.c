/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:49:25 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/04/15 13:50:57 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_commands(t_input *input, __unused t_envp *envp_mx)
{
	int	i;

	input->line_sp = ft_split(input->line, ';');
	i = -1;
	while (input->line_sp[++i])
	{
		input->command = ft_split(input->line_sp[i], '|');
		execute_commands(input->command, envp_mx);
		free_array((void **)input->command);
	}
	free_array((void **)input->line_sp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_mx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:27:22 by xortega           #+#    #+#             */
/*   Updated: 2024/04/08 12:36:06 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_mx(t_envp **envp_mx, char *variable)
{
	t_envp	*current;

	if (!*envp_mx)
		return ;
	current = *envp_mx;
	while (current)
	{
		if (!ft_strncmp(current->variable, variable, ft_strlen(variable)))
			current->exported = true;
		current = current->next;
	}
}

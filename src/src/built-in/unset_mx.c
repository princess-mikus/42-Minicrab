/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_mx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:32:00 by xortega           #+#    #+#             */
/*   Updated: 2024/04/08 14:33:08 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_mx(t_envp **envp_mx, char *variable)
{
	t_envp	*current;
	t_envp	*next;

	if (!*envp_mx)
		return ;
	current = *envp_mx;
	next = current->next;
	while (next)
	{
		if (!ft_strncmp(next->variable, variable, ft_strlen(variable)))
		{
			current->next = next->next;
			free(next->content);
			free(next->variable);
			free(next);
			return ;
		}
		current = current->next;
		next = next->next;
	}
}

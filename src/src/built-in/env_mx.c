/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:19:18 by xortega           #+#    #+#             */
/*   Updated: 2024/04/08 12:24:12 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_mx(t_envp **envp_mx)
{
	t_envp	*current;

	if (!*envp_mx)
		return ;
	current = *envp_mx;
	while (current->next)
	{
		if (current->exported)
			printf("%s=%s\n", current->variable, current->content);
		current = current->next;
	}
}

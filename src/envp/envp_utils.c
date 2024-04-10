/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:53:23 by xortega           #+#    #+#             */
/*   Updated: 2024/04/10 11:18:13 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_envp(t_envp **envp_mx, char *variable)
{
	t_envp	*current;

	if (!*envp_mx)
		return (0);
	current = *envp_mx;
	while (current)
	{
		if (!ft_strncmp(current->variable, variable, ft_strlen(variable)))
			return (1);
		current = current->next;
	}
	return (0);
}

char	*get_content_envp_mx(t_envp **envp_mx, char *variable)
{
	t_envp	*current;

	if (!*envp_mx)
		return (NULL);
	current = *envp_mx;
	while (current)
	{
		if (!ft_strncmp(current->variable, variable, \
			ft_strlen(variable)))
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:53:23 by xortega           #+#    #+#             */
/*   Updated: 2024/05/17 13:12:57 by mikus            ###   ########.fr       */
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

t_envp	*get_node_envp_mx(t_envp **envp_mx, char *variable)
{
	t_envp	*current;

	if (!*envp_mx || !variable)
		return (NULL);
	current = *envp_mx;
	while (current)
	{
		if (!ft_strncmp(current->variable, variable, \
			ft_strlen(variable)))
			return (current);
		current = current->next;
	}
	return (NULL);
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
	return ("");
}

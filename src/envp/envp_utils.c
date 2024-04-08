/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:53:23 by xortega           #+#    #+#             */
/*   Updated: 2024/04/08 12:01:22 by xortega          ###   ########.fr       */
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

void	envp_erase(t_envp **envp_mx, char *variable)
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

t_envp	*new_envp(char *variable, char *content)
{
	t_envp	*node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->content = content;
	node->variable = variable;
	node->exported = false;
	node->next = NULL;
	return (node);
}

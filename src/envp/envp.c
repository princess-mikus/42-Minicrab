/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:58:58 by xortega           #+#    #+#             */
/*   Updated: 2024/04/08 11:55:02 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_add(t_envp **envp_mx, t_envp *new)
{
	t_envp	*current;

	if (!*envp_mx)
		*envp_mx = new;
	else
	{
		current = *envp_mx;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	init_envp(t_envp **envp_mx, char **envp)
{
	int		i;
	t_envp	*current;

	if (envp == NULL || *envp == NULL)
		return ;
	i = -1;
	while (envp[++i])
		envp_add(envp_mx, new_envp(ft_substr(envp[i], 0, \
		(ft_strchr(envp[i], '=') - envp[i])), \
		ft_strdup(ft_strchr(envp[i], '=') + 1)));
	current = *envp_mx;
	envp_erase(envp_mx, "OLDPWD");
	while (current)
	{
		export_mx(envp_mx, current->variable);
		current = current->next;
	}
}

void	print_envp(t_envp **envp_mx)
{
	t_envp	*current;

	current = *envp_mx;
	while (current->next)
	{
		printf("VARIABLE:\t%s\n", current->variable);
		printf("CONTENT:\t%s\n", current->content);
		printf("EXPORT:\t%d\n", current->exported);
		current = current->next;
	}
}

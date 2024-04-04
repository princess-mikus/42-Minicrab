/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:58:58 by xortega           #+#    #+#             */
/*   Updated: 2024/04/04 15:44:14 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_envp	*new_envp(char *variable, char *content)
{
	t_envp	*node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->content = content;
	node->variable = variable;
	node->next = NULL;
	return (node);
}

void	init_envp(t_envp **envp_mx, char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		envp_add(envp_mx, new_envp(ft_substr(envp[i], 0, \
		(ft_strchr(envp[i], '=') - envp[i])), \
		ft_strdup(ft_strchr(envp[i], '=') + 1)));
	envp_erase(envp_mx, "OLDPWD");
}

void	print_envp(t_envp **envp_mx)
{
	t_envp	*current;

	current = *envp_mx;
	while (current->next)
	{
		printf("VARIABLE:\t%s\n", current->variable);
		printf("CONTENT:\t%s\n", current->content);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*envp_mx;

	argc = 1;
	argv = NULL;
	envp_mx = NULL;
	init_envp(&envp_mx, envp);
	print_envp(&envp_mx);
	return (0);
}

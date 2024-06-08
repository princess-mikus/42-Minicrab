/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:58:58 by xortega           #+#    #+#             */
/*   Updated: 2024/06/08 14:48:13 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_add_back(t_envp **envp_mx, t_envp *new)
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
	char	*temp[2];
	t_envp	*current;

	if (envp == NULL || *envp == NULL)
		return ;
	i = -1;
	while (envp[++i])
		envp_add_back(envp_mx, new_envp(ft_substr(envp[i], 0, \
		(ft_strchr(envp[i], '=') - envp[i])), \
		ft_strdup(ft_strchr(envp[i], '=') + 1)));
	unset_mx(envp_mx, "OLDPWD");
	current = *envp_mx;
	while (current)
	{
		temp[0] = current->variable;
		temp[1] = NULL;
		export_mx(envp_mx, temp, NULL);
		current = current->next;
	}
	envp_add_back(envp_mx, new_envp(ft_strdup("~"), \
		ft_strdup(get_content_envp_mx(envp_mx, "HOME"))));
	envp_add_back(envp_mx, new_envp(ft_strdup("?"), ft_strdup("0")));
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

void	add_var_to_envp_mx(t_envp **envp_mx, char *variable, char *content)
{
	if (!is_envp(envp_mx, variable))
		envp_add_back(envp_mx, new_envp(variable, content));
	else
	{
		free(get_node_envp_mx(envp_mx, variable)->content);
		get_node_envp_mx(envp_mx, variable)->content = content;
	}
}

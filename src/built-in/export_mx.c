/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_mx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:27:22 by xortega           #+#    #+#             */
/*   Updated: 2024/06/07 14:48:06 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argv_case(t_envp **envp_mx, char *variable)
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

void	dec_case(t_envp **envp_mx, t_file **dec)
{
	int		i;
	t_envp	*current;

	dec_to_env(dec, envp_mx);
	current = *envp_mx;
	while (current)
	{
		i = 0;
		while (dec[i])
		{
			if (!ft_strncmp(current->variable, \
				dec[i]->name, ft_strlen(dec[i]->name)))
				current->exported = true;
			i++;
		}
		current = current->next;
	}
}

void	export_mx(t_envp **envp_mx, char **argv, t_file **dec)
{
	int		i;

	i = 0;
	while (argv && argv[i])
	{
		argv_case(envp_mx, argv[i]);
		i++;
	}
	if (dec)
		dec_case(envp_mx, dec);
}

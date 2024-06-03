/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:47:57 by mikus             #+#    #+#             */
/*   Updated: 2024/06/03 10:43:20 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_environment(t_command *current, t_envp **envp_mx)
{
	t_envp	*envp_mx_temp;
	char	**envp;

	envp_mx_temp = NULL;
	envp = envp_mx_to_arg(envp_mx);
	if (current->dec)
	{
		init_envp(&envp_mx_temp, envp);
		free(envp);
		dec_to_env(current->dec, &envp_mx_temp);
		envp = envp_mx_to_arg(&envp_mx_temp);
		free_envp_mx(&envp_mx_temp);
	}
	return (envp);
}

void	dec_to_env(t_file **dec, t_envp **envp_mx_temp)
{
	int		i;
	char	*variable;
	char	*content;
	char	**temp;

	i = 0;
	while (dec[i])
	{
		temp = ft_split(dec[i]->name, '=');
		variable = ft_strdup(temp[0]);
		content = ft_strdup(temp[1]);
		free_array((void **)temp);
		add_var_to_envp_mx(envp_mx_temp, variable, content);
		i++;
	}
}

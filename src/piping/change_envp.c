/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:47:57 by mikus             #+#    #+#             */
/*   Updated: 2024/06/07 14:00:19 by fcasaubo         ###   ########.fr       */
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

char	*get_var_content_escaped(char *content)
{
	char	*temp;
	char	*to_return;

	temp = ft_strjoin("'", content);
	to_return = ft_strjoin(temp, "'");
	free(temp);
	return (to_return);
}

void	dec_to_env(t_file **dec, t_envp **envp_mx_temp)
{
	int		i;
	char	*variable;
	char	*content;
	char	*trimmed;

	i = 0;
	while (dec[i])
	{
		trimmed = ft_strtrim(dec[i]->name, " ");
		variable = ft_substr(trimmed, 0, ft_strlen(trimmed) \
		- ft_strlen(ft_strchr(trimmed, '=')));
		content = get_var_content_escaped(ft_strchr(trimmed, '=') + 1);
		free(trimmed);
		add_var_to_envp_mx(envp_mx_temp, variable, content);
		i++;
	}
}

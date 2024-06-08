/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:19:18 by xortega           #+#    #+#             */
/*   Updated: 2024/06/08 17:31:17 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_mx(t_envp **envp_mx)
{
	t_envp	*current;
	char	*temp;

	if (!*envp_mx)
		return ;
	current = *envp_mx;
	while (current)
	{
		if (ft_strlen(current->content) > 2)
			temp = ft_strtrim(current->content, "\'");
		else
			temp = ft_strdup("");
		if (current->exported)
			ft_printf("%s=%s\n", current->variable, temp);
		free(temp);
		current = current->next;
	}
}

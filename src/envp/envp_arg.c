/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:43 by xortega           #+#    #+#             */
/*   Updated: 2024/06/07 15:05:31 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_mx_num(t_envp **envp_mx)
{
	t_envp	*current;
	int		size;

	current = *envp_mx;
	size = 0;
	while (current)
	{
		if (current->exported == true)
			size++;
		current = current->next;
	}
	return (size);
}

/*
char	*make_line_envp(char *variable, char *content)
{
	char	*line;
	int		variable_len;
	int		content_len;

	variable_len = ft_strlen(variable);
	content_len = ft_strlen(content);
	line = ft_calloc(sizeof(char), (variable_len + content_len + 2));
	ft_strlcat(line, variable, variable_len + 1);
	ft_strlcat(line, "=", variable_len + 2);
	ft_strlcat(line, content, variable_len + 2 + content_len);
	return (line);
}
*/

char	*make_line_envp(char *variable, char *content)
{
	char	*line;
	char	*temp;

	temp = ft_strjoin(variable, "=");
	line = ft_strjoin(temp, content);
	free(temp);
	return (line);
}

char	**envp_mx_to_arg(t_envp **envp_mx)
{
	t_envp	*current;
	char	**envp_new;
	int		i;

	if (!*envp_mx)
		return (NULL);
	current = *envp_mx;
	envp_new = malloc(sizeof(char *) * (envp_mx_num(envp_mx) + 1));
	i = 0;
	while (current)
	{
		if (current->exported == true)
		{
			envp_new[i] = make_line_envp(current->variable, current->content);
			i++;
		}
		current = current->next;
	}
	envp_new[i] = NULL;
	return (envp_new);
}

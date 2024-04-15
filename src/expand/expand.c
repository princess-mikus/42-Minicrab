/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:05 by xortega           #+#    #+#             */
/*   Updated: 2024/04/10 17:07:06 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_len(t_envp **envp_mx, char *imput)
{
	int		len;
	int		i;
	char	*variable;

	len = 0;
	i = 0;
	while (imput[i])
	{
		if (imput[i] == '$')
		{
			i++;
			variable = ft_substr(imput, i, \
				(ft_strchr(imput + i, ' ') - imput) - i);
			len += ft_strlen(get_content_envp_mx(envp_mx, variable));
			free(variable);
			while (imput[i] && imput[i] != ' ')
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*expansion(t_envp **envp_mx, char *imput)
{
	char	*line;
	char	*variable;
	int		i;
	int		k;

	i = 0;
	k = 0;
	line = ft_calloc(sizeof(char), line_len(envp_mx, imput));
	while (imput[i])
	{
		if (imput[i] == '$')
		{
			i++;
			variable = ft_substr(imput, i, \
				(ft_strchr(imput + i, ' ') - imput) - i);
			k = ft_strlcat(line, get_content_envp_mx(envp_mx, variable), \
	(ft_strlen(line) + ft_strlen(get_content_envp_mx(envp_mx, variable)) + 1));
			free(variable);
			while (imput[i] && imput[i] != ' ')
				i++;
		}
		else
			line[k++] = imput[i++];
	}
	return (line);
}

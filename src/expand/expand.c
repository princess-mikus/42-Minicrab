/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:05 by xortega           #+#    #+#             */
/*   Updated: 2024/06/02 16:40:18 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_len(t_envp **envp_mx, char *input)
{
	int		len;
	int		i;
	char	*var;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			var = ft_substr(input, i, \
				(ft_strchr(input + i, ' ') - input) - i);
			if (!get_content_envp_mx(envp_mx, var))
				len += 0;
			else
				len += ft_strlen(get_content_envp_mx(envp_mx, var));
			free(var);
			while (input[i] && input[i] != ' ')
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

char	*expansion(t_envp **envp_mx, char *input)
{
	char	*line;
	char	*var;
	int		i;
	int		k;

	i = 0;
	k = 0;
	line = ft_calloc(sizeof(char), line_len(envp_mx, input) + 1);
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			var = ft_substr(input, i, \
			(ft_strchr(input + i, ' ') - input) - i);
			if (!get_content_envp_mx(envp_mx, var))
				k = 0;
			else
				k = ft_strlcat(line, get_content_envp_mx(envp_mx, var), \
				(ft_strlen(line) + ft_strlen(get_content_envp_mx(envp_mx, var)) + 1));
			free(var);
			while (input[i] && input[i] != ' ')
				i++;
		}
		else if (input[i] == '~')
		{
			i++;
			k = ft_strlcat(line, get_content_envp_mx(envp_mx, "~"), \
			(ft_strlen(line) + ft_strlen(get_content_envp_mx(envp_mx, "~")) + 1));
		}
		else
			line[k++] = input[i++];
	}
	return (line);
}

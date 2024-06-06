/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:05 by xortega           #+#    #+#             */
/*   Updated: 2024/06/06 16:47:48 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	normal_len(int *i, t_envp **envp_mx, char *input)
{
	char	*var;
	char	*temp;
	int		len;

	*i += 1;
	if (ft_strchr(input + *i, ' '))
		temp = ft_substr(input, *i, \
		(ft_strchr(input + *i, ' ') - input) - *i);
	else
		temp = ft_substr(input, *i, \
		ft_strlen(input) - *i);
	var = ft_strtrim(temp, "\"");
	free(temp);
	if (!get_content_envp_mx(envp_mx, var))
		len = 0;
	else
		len = ft_strlen(get_content_envp_mx(envp_mx, var) + 1);
	free(var);
	if (input[*i] == ' ')
		len += 1;
	while (input[*i] && input[*i] != ' ' && input[*i] != '"')
		*i += 1;
	return (len);
}

int	line_len(t_envp **envp_mx, char *input)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			len += normal_len(&i, envp_mx, input);
		}
		else if (input[i] == '~')
		{
			i++;
			if (!get_content_envp_mx(envp_mx, "~"))
				len += 0;
			else
				len += ft_strlen(get_content_envp_mx(envp_mx, "~") + 1);
		}
		len++;
		i++;
	}
	return (len);
}

char	*return_next(bool *space, char *input, int i)
{
	char	*contender;
	char	*contender2;

	contender = ft_strchr(input + i, ' ');
	contender2 = ft_strchr(input + i, '$');

	if (!contender2)
	{
		*space = false;
		return (contender);
	}
	if (contender && ft_strlen(contender) > ft_strlen(contender2))
	{
		*space = true;
		return (contender2);
	}
	*space = false;
	return (contender2);
}

static int	normal_case(int *i, t_envp **envp_mx, char *line, char *input)
{
	char	*var;
	char	*temp;
	int		k;

	*i += 1;
	if (ft_strchr(input + *i, ' '))
		temp = ft_substr(input, *i, \
		(ft_strchr(input + *i, ' ') - input) - *i);
	else
		temp = ft_substr(input, *i, \
		ft_strlen(input) - *i);
	var = ft_strtrim(temp, "\"");
	free(temp);
	if (!get_content_envp_mx(envp_mx, var))
		k = 0;
	else
		k = ft_strlcat(line, get_content_envp_mx(envp_mx, var), \
		(ft_strlen(line) + ft_strlen(get_content_envp_mx(envp_mx, var)) + 1));
	free(var);
	while (input[*i] && (input[*i] != ' ' && input[*i] != '"'))
		*i += 1;
	k -= (input[*i] == '"');
	ft_printf("line === [%s]\n", line);
	ft_printf("input === [%s]\n", input + *i);
	return (k);
}

char	*expansion(t_envp **envp_mx, char *input)
{
	char	*line;
	int		i;
	int		k;

	i = 0;
	k = 0;
	line = ft_calloc(sizeof(char), line_len(envp_mx, input) + 2);
	ft_printf("[%d]\n", line_len(envp_mx, input) + 1);
	while (input[i])
	{
		if (input[i] == '$')
			k += normal_case(&i, envp_mx, line, input);
		else if (input[i] == '~')
		{
			i++;
			k = ft_strlcat(line, get_content_envp_mx(envp_mx, "~"), \
			(ft_strlen(line) + ft_strlen(get_content_envp_mx(envp_mx, "~")) \
			+ 1));
			while (input[i] && input[i] != ' ')
				i++;
		}
		line[k++] = input[i++];
	}
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:05 by xortega           #+#    #+#             */
/*   Updated: 2024/06/03 11:06:42 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	normal_len(int *i, t_envp **envp_mx, char *input)
{
	char	*var;
	int		len;

	len = 0;
	*i += 1;
	var = ft_substr(input, *i, \
		(ft_strchr(input + *i, ' ') - input) - *i);
	if (!get_content_envp_mx(envp_mx, var))
		len = 0;
	else
		len = ft_strlen(get_content_envp_mx(envp_mx, var) + 1);
	free(var);
	if (input[*i] == ' ')
		len += 1;
	while (input[*i] && input[*i] != ' ')
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
			len += normal_len(&i, envp_mx, input);
		else if (input[i] == '~')
		{
			i++;
			if (!get_content_envp_mx(envp_mx, "~"))
				len += 0;
			else
				len += ft_strlen(get_content_envp_mx(envp_mx, "~") + 1);
		}
		else
		{
			len++;
			i++;
		}
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
	char	*next;
	bool	space;
	int		k;

	*i += 1;
	next = return_next(&space, input, *i);
	ft_printf("%s\n", next);
	var = ft_substr(input, *i, \
	(next - input) - *i);
	if (!get_content_envp_mx(envp_mx, var))
		k = 0;
	else
		k = ft_strlcat(line, get_content_envp_mx(envp_mx, var), \
		(ft_strlen(line) + ft_strlen(get_content_envp_mx(envp_mx, var)) + 1));
	free(var);
	while (input[*i] && input[*i] != ' ')
		*i += 1;
	return (k);
}

char	*expansion(t_envp **envp_mx, char *input)
{
	char	*line;
	int		i;
	int		k;

	i = 0;
	k = 0;
	line = ft_calloc(sizeof(char), line_len(envp_mx, input) + 1);
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
		else
			line[k++] = input[i++];
	}
	return (line);
}

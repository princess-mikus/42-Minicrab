/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:05 by xortega           #+#    #+#             */
/*   Updated: 2024/06/08 16:34:56 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_betwen_quotes(char *line, int i)
{
	int	j;
	int	status_1;
	int	status_2;

	j = 0;
	status_1 = 0;
	status_2 = 0;
	while (line[j])
	{
		if (line[j] == '\"' && status_2 % 2 == 0)
			status_1++;
		if (line[j] == '\'' && status_1 % 2 == 0)
			status_2++;
		if (j == i && status_2 % 2 != 0)
			return (false);
		j++;
	}
	return (true);
}

t_envp	*next_node(t_envp **envp_mx, char *input)
{
	t_envp	*node;
	int		len;
	char	*temp;

	len = 0;
	while (input[len] && input[len] != ' ' && input[len] != '$'
		&& input[len] != '"' && input[len] != '\'')
		len++;
	temp = ft_substr(input, 0, len);
	node = get_node_envp_mx(envp_mx, temp);
	free(temp);
	return (node);
}

int	normal_len(int *i, t_envp **envp_mx, char *input)
{
	int		len;
	int		start;
	char	*temp;

	len = 0;
	start = *i + 1;
	*i += 1;
	while (input[*i] && input[*i] != ' ' && input[*i] != '$'
		&& input[*i] != '"' && input[*i] != '\'')
	{
		len++;
		*i += 1;
	}
	*i -= 1;
	temp = ft_substr(input, start, len);
	if (get_content_envp_mx(envp_mx, temp))
		len = ft_strlen(get_content_envp_mx(envp_mx, temp));
	return (len - 1);
}

int	line_len(t_envp **envp_mx, char *input)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == '$' && is_betwen_quotes(input, i))
			len += normal_len(&i, envp_mx, input);
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

static int	normal_case(int *i, t_envp **envp_mx, char *line, char *input)
{
	int	k;

	if (!next_node(envp_mx, input + *i + 1))
	{
		*i += 1;
		while (input[*i] && input[*i] != ' ' && input[*i] != '$'
			&& input[*i] != '"' && input[*i] != '\'')
			*i += 1;
		return (0);
	}
	k = ft_strlen(next_node(envp_mx, input + *i + 1)->content);
	ft_strlcat(line, next_node(envp_mx, input + *i + 1)->content,
		ft_strlen(line) + k + 1);
	*i += ft_strlen(next_node(envp_mx, input + *i + 1)->variable) + 1;
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
		while (input[i] == '$' && is_betwen_quotes(input, i))
			k += normal_case(&i, envp_mx, line, input);
		while (input[i] == '~')
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:05 by xortega           #+#    #+#             */
/*   Updated: 2024/04/10 12:04:26 by xortega          ###   ########.fr       */
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

int	main(void)
{
	t_envp	*envp_mx;
	char	*expanded;

	envp_mx = NULL;
	add_var_to_envp_mx(&envp_mx, "variable", "123");
	add_var_to_envp_mx(&envp_mx, "variable2", "abcd");
	add_var_to_envp_mx(&envp_mx, "variable3", "666666");
	printf("line_len before expansion : %zu\n", ft_strlen("123 $variable 123 $variable2 $variable3"));
	printf("line_len after expansion : %d\n", line_len(&envp_mx, "123 $variable 123 $variable2 $variable3"));
	printf("line_len expeted : %zu\n", ft_strlen("123 123 123 abcd 666666"));
	expanded = expansion(&envp_mx, "123 $variable 123 $variable2 $variable3");
	printf("line expanded :\t[%s]\n", expanded);
	free(expanded);
	printf("line expeted :\t[%s]\n", "123 123 123 abcd 666666");
	printf("--------------------------------------\n");
	expanded = expansion(&envp_mx, "$variable3 $variable2");
	printf("line expanded :\t%s\n", expanded);
	free(expanded);
	expanded = expansion(&envp_mx, " $variable3 $variable2 ");
	printf("line expanded :\t%s\n", expanded);
	free(expanded);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:07:56 by mikus             #+#    #+#             */
/*   Updated: 2024/04/08 23:29:03 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*replace(char *str, char **variables)
{
	int		i;
	int		var_num;
	int		offset;
	int		len;
	char	*new_text;

	i = -1;
	offset = 0;
	var_num = 0;
	len = ft_strlen(str);
	while (variables[++i])
		len += ft_strlen(variables[i]);
	i = 0;
	new_text = malloc(sizeof(char) * len);
	while (str[i])
	{
		if (str[i] == '$')
		{
			offset = ft_strlcat(new_text, variables[var_num], ft_strlen(new_text) + ft_strlen(variables[var_num]) + 1) - ft_strlen(new_text);
			var_num++;
			while (str[i + 1] && str[i + 1] != ' ')
				i++;
		}
		else
			new_text[i + offset] = str[i]; 
		i++;
	}
	return (new_text);
}
char	*expand(char *str, t_enviroment *env)
{
	int		end;
	char	*name;

	end = 0;
	while (str[end] && str[end] != ' ')
		end++;
	name = ft_substr(str, 1, end);
	while (env)
	{
		if (!ft_strncmp(name, env->name, ft_strlen(env->name)))
			break ;
		env = env->next;
	}
	free(name);
	if (env)
		return (env->content);
	return (ft_strdup("\0"));
}

int	var_counter(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (str[++i])
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || \
		str[i + 1] == '!' || str[i + 1] == '-' || str[i + 1] == '_'))
			num++;
	return (num);
}

void	*expander(char *line, t_envp *envp_mx)
{
	char	*new_line;
	char	**variables;
	int		number_of_vars;
	int		i;
	int		offset;

	number_of_vars = var_counter(*str);
	variables = malloc(number_of_vars * sizeof(char *));
	i = -1;
	offset = 0;
	while (++i < number_of_vars)
	{
		variables[i] = expand(ft_strchr(str + offset, '$'), env);
		offset += ft_strlen(ft_strchr(str + offset, '$') + 1);
	}
	variables[i] = NULL;
	new_line = replace(str, variables);
	free(str);
	return (new_line);
}

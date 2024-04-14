/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:50 by xortega           #+#    #+#             */
/*   Updated: 2024/04/04 15:43:57 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/ft_strlen.c"
#include "../libft/ft_isalpha.c"
#include "../libft/ft_strrchr.c"
#include "../libft/ft_memmove.c"
#include "../libft/ft_strdup.c"
#include "../libft/ft_strchr.c"
#include "../libft/ft_strlcat.c"
#include "../libft/ft_strncmp.c"
#include "../libft/ft_substr.c"

typedef struct s_enviroment
{
	char				*name;
	char				*content;
	struct s_enviroment	*next;
}	t_enviroment;


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

void	*expander(char **str, t_enviroment	*env)
{
	char	*expanded;
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
		variables[i] = expand(ft_strchr(*str + offset, '$'), env);
		offset += ft_strlen(ft_strchr(*str + offset, '$') + 1);
	}
	variables[i] = NULL;
	expanded = replace(*str, variables);
	free(*str);
	return (expanded);
}

int	main(int argc, char **argv)
{
	char			*str;
	t_enviroment	var1;
	t_enviroment	var2;
	t_enviroment	var3;
	t_enviroment	var4;

	var1.name = "HOLA";
	var1.content = "QUE TAL";
	var1.next = &var2;
	var2.name = "CHAU";
	var2.content = "GIL";
	var2.next = &var3;
	var3.name = "ONDA";
	var3.content = "QUE";
	var3.next = &var4;
	var4.name = "X";
	var4.content = "XD";
	var4.next = NULL;
	if (argc == 2)
		str = ft_strdup(argv[1]);
	else
		str = ft_strdup("Hola $X $HOLA a");
	printf("%s\nVS\n", str);
	str = expander(&str, &var1);
	printf("%s\n", str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:05 by xortega           #+#    #+#             */
/*   Updated: 2024/04/23 16:09:13 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_alpha(char *str)
{
	int i;

	i  = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			return (str + i);
		i++;
	}
	return (NULL);
}


int	new_infile(char *line, t_command *node)
{
	if (ft_strchr(line, '<')) //haz una funcion que devuelva true cuando un caracter c esta en el str pero esta fuera de dobles comillas
	{	
		if (!ft_strchr(line , '"')) //no hay caracter " : " hola ls"
			node->infile = (ft_substr(line, search_alpha(line) - line,\
				ft_strchr(search_alpha(line), ' ') - line));
		else
		{
			if (search_alpha(line) - line > ft_strchr(line , '"') - line) //si el " esta antes de cualquier caracter : "" hola" jiji"
				node->infile = (ft_substr(line, ft_strchr(line, '"') - line,
					ft_strchr(ft_strchr(line, '"') + 1, '"') - line));
			else // el caracter " esta despues de cualquier otro caracter : " hola "jiji""
				node->infile = (ft_substr(line, search_alpha(line) - line,
					ft_strchr(search_alpha(line), ' ') - line));
		}
		return (ft_strchr(line, '<') - line);
	}
	node->infile = NULL;
	return (0);
}

t_command *new_command(char *line)
{
	t_command	*new;
	int			offset;

	offset = 0;
	new = malloc(sizeof(t_command));
	// < infile commmand flags > outfile
	offset = new_infile(ft_strchr(line, '<'), new); //haz una funcion que devuelva true cuando un caracter c esta en el str pero esta fuera de dobles comillas
	//repite el modelo de funcion que devuelve el offset, que reciba line + offset y que busque con la misma logica el comando, repite con las flags y con el outfile
	
	
}

void	add_command(char *line_expanded, t_command **commands)
{
	t_command	*current;

	current = *commands;
	if (!current)
		*commands = new_command(line_expanded);
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_command(line_expanded);
	}
}

void	parse(char *line_expanded, t_command **commands)
{
	char	**splited;
	int		i;

	splited = ft_split(line_expanded, '|');
	i = 0;
	while (splited[i])
	{
		add_command(splited[i], commands);
		i++;
	}
}

int main(void)
{
	char *line1 = " hola jiji";
	char *line2 = " \" hola \"jiji";
	char *line3 = " hola \"jiji\"";
	

	printf("%s\n", line1);
	printf("%s\n", new_infile(line1));
	printf("%s\n", line2);
	printf("%s\n", new_infile(line2));
	printf("%s\n", line3);
	printf("%s\n", new_infile(line3));
	//printf("line1 \"hola\"\n");
	//printf("%ld\n", search_alpha(line1) - line1);
	//printf("%ld\n", ft_strchr(line1, '"') - line1);
	//printf("line2 \"\"hola\"\"\n");
	//printf("%ld\n", search_alpha(line2) - line2);
	//printf("%ld\n", ft_strchr(line2, '"') - line2);
	//printf("line3 \"hola \"jiji\"\"\n");
	//printf("%ld\n", search_alpha(line3) - line3);
	//printf("%ld\n", ft_strchr(line3, '"') - line3);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:05 by xortega           #+#    #+#             */
/*   Updated: 2024/04/30 13:03:24 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rsearch_alpha(char *str)
{
	int i;

	i  = ft_strlen(str);
	while (i > 0)
	{
		if (ft_isalnum(str[i]) || str[i] == '-')
			return (str + i);
		i--;
	}
	return (NULL);
}

char	*search_alpha(char *str)
{
	int i;

	i  = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '-')
			return (str + i);
		i++;
	}
	return (NULL);
}


void	new_outfile(char *line, t_command *node)
{
	if (ft_strchr(line, '>'))
	{
		node->outfile = ft_substr(line, 
			search_alpha(ft_strchr(line, '>')) - line,
				 rsearch_alpha(line) - line);
	}
}
void	new_arg(char *line, t_command *node)
{
	char *temp;

	if (search_alpha(line) == NULL)
		return ;
	if (ft_strchr(line, '>'))
	{
		temp = ft_substr(line, 0, (ft_strchr(line, '>')) - line);
		node->arg = ft_substr(temp, 0, rsearch_alpha(temp) - temp);
		free(temp);
	}
	else
	{
		node->arg = ft_substr(line, 0, 
			rsearch_alpha(line) - line);
	}
}
int	new_cmd(char *line, t_command *node)
{
	node->command = ft_substr(line, 0, ft_strchr(line, ' ') - line);
	return (search_alpha(ft_strchr(line, ' ')) - line); // + 1 ?????
}
int	new_infile(char *line, t_command *node)
{
	printf("search ; [%ld]\n", ft_strchr(search_alpha(line), ' ') - line);
	if (ft_strchr(line, '<')) //haz una funcion que devuelva true cuando un caracter c esta en el str pero esta fuera de dobles comillas
	{	
		if (!ft_strchr(line , '"')) //no hay caracter '"' : " hola ls"
			node->infile = (ft_substr(line, search_alpha(line) - line,\
				ft_strchr(search_alpha(line), ' ') - search_alpha(line)));
		else
		{
			if (search_alpha(line) - line > ft_strchr(line , '"') - line) //si el " esta antes de cualquier caracter : "" hola" jiji"
				node->infile = (ft_substr(line, ft_strchr(line, '"') - line,
					ft_strchr(ft_strchr(line, '"') + 1, '"') - line));
			else // el caracter " esta despues de cualquier otro caracter : " hola "jiji""
				node->infile = (ft_substr(line, search_alpha(line) - line,
					ft_strchr(search_alpha(line), ' ') - line));
		}
		return (search_alpha(ft_strchr(line, '<')) - line);
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
	new->infile = NULL;
	new->command = NULL;
	new->arg = NULL;
	new->outfile = NULL;
	// < infile commmand flags > outfile
	offset += new_infile(line, new);
	offset += new_cmd(search_alpha(line + offset), new);
	new_arg(search_alpha(line + offset), new);
	new_outfile(search_alpha(line), new);
	return(new);
	//repite el modelo de funcion que devuelve el offset, que reciba line + offset y que busque con la misma logica el comando, repite con las flags y con el outfile
	//haz una funcion que devuelva true cuando un caracter c esta en el str pero esta fuera de dobles comillas
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
	char *line1 = "hey    <    hola    -s    -l      jiji    >    hihi    ";
	//char *line2 = " \" hola \"jiji";
	//char *line3 = " hola \"jiji\"";
	t_command *command;
	
	command = new_command(line1);
	printf("%s\n", line1);
	printf("infile:[%s]\n", command->infile);
	printf("command:[%s]\n", command->command);
	printf("arg:[%s]\n", command->arg);
	ft_strt
	printf("outfile:[%s]\n", command->outfile);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:05 by xortega           #+#    #+#             */
/*   Updated: 2024/05/02 13:58:13 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rsearch_alpha(char *str)
{
	int i;

	i  = ft_strlen(str);
	while (str && i > 0)
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
	while (str && str[i] != '\0')
	{
		if (ft_isalnum(str[i]) || str[i] == '-')
			return (str + i);
		i++;
	}
	return (NULL);
}


void	new_arg(char *line, t_command *node)
{
	char *temp;

	if (search_alpha(line) == NULL)
		return ;
	if (ft_strchr(line, '>'))
	{
		temp = ft_substr(line, 0, (ft_strchr(line, '>')) - line);
		node->arg = ft_strtrim(temp, " ");
		free(temp);
	}
	else if (ft_strchr(line, '<'))
	{
		temp = ft_substr(line, 0, (ft_strchr(line, '<')) - line);
		node->arg = ft_strtrim(temp, " ");
		free(temp);
	}
	else
	{
		node->arg = ft_substr(line, 0, 
			rsearch_alpha(line) + 1 - line);
	}
}
int	new_cmd(char *line, t_command *node)
{
	if (ft_strchr(line, ' '))
	{
		node->command = ft_substr(line, 0, ft_strchr(line, ' ') - line);
		return (ft_strchr(line, ' ') - line);
	}
	node->command = ft_substr(line, 0, ft_strlen(line));
	return (ft_strlen(line));
}
int	new_outfile(char *line, t_command *node)
{
	if (ft_strchr(line, '>') && ft_strchr(search_alpha(
		ft_strchr(line, '>')), ' ') && ft_strchr(line, '>')[1] == ' ') // the outfile is at the beggining and there are spaces betwen the > and the filename
	{
		node->outfile = ft_substr(line, search_alpha(line + 1) - line, 
		ft_strchr(search_alpha(line + 1), ' ') - search_alpha(line + 1));
		return (search_alpha(ft_strchr(
			search_alpha(ft_strchr(line, '>')), ' ')) - line);
	}
	else if (ft_strchr(line, '>') && ft_strchr(
		search_alpha(ft_strchr(line, '>')), ' ')) // the outfile is at the beggining and there are not spaces betwen the > and the filename
	{
		node->outfile = ft_substr(line, 1, ft_strchr(line, ' ') - line - 1);
		return (search_alpha(ft_strchr(line, ' ')) - line);
	}
	else if (ft_strchr(line, '>') && ft_strchr(line, '>')[1] == ' ')  // the outfile is at the end and there are spaces betwen the > and the filename
		node->outfile = ft_substr(line,
			search_alpha(ft_strchr(line, '>')) - line,
			ft_strlen(search_alpha(ft_strchr(line, '>'))));	
	else if (ft_strchr(line, '>'))// the outfile is at the end and there are not spaces betwen the > and the filename
		node->outfile = ft_substr(line,
			ft_strchr(line, '>') - line + 1,
			ft_strlen(search_alpha(ft_strchr(line, '>'))));
	return (0);
}
int	new_infile(char *line, t_command *node)
{
	if (ft_strchr(line, '<') && ft_strchr(search_alpha(
		ft_strchr(line, '<')), ' ') && ft_strchr(line, '<')[1] == ' ') // the infile is at the beggining and there are spaces betwen the > and the filename
	{
		node->infile = ft_substr(line, search_alpha(line + 1) - line, 
		ft_strchr(search_alpha(line + 1), ' ') - search_alpha(line + 1));
		return (search_alpha(ft_strchr(
			search_alpha(ft_strchr(line, '<')), ' ')) - line);
	}
	else if (ft_strchr(line, '<') && ft_strchr(
		search_alpha(ft_strchr(line, '<')), ' ')) // the infile is at the beggining and there are not spaces betwen the > and the filename
	{
		node->infile = ft_substr(line, 1, ft_strchr(line, ' ') - line - 1);
		return (search_alpha(ft_strchr(line, ' ')) - line);
	}
	else if (ft_strchr(line, '<') && ft_strchr(line, '<')[1] == ' ')  // the infile is at the end and there are spaces betwen the > and the filename
		node->infile = ft_substr(line,
			search_alpha(ft_strchr(line, '<')) - line,
			ft_strlen(search_alpha(ft_strchr(line, '<'))));	
	else if (ft_strchr(line, '<'))// the infile is at the end and there are not spaces betwen the > and the filename
		node->infile = ft_substr(line,
			ft_strchr(line, '<') - line + 1,
			ft_strlen(search_alpha(ft_strchr(line, '<'))));
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
	offset += new_outfile(line, new);
	offset += new_cmd(line + offset, new);
	new_arg(search_alpha(line + offset), new);
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
	char *line1 = "   > outfile    ls    -l   -a    < infile ";
	//char *line1 = "   > o    l    a    < i ";
	//char *line1 = " <     infile    ls    -la    >    outfile";
	//char *line1 = " <      infile    ls   -la    ";
	//char *line1 = " ls -la  > outfile";
	//char *line1 = " ls -la ";
	//char *line1 = " ls ";
	char *line;
	t_command *command;
	
	line = ft_strtrim(line1, " ");
	command = new_command(line);
	

	printf("line:[%s]\n", line);
	printf("infile:[%s]\n", command->infile);
	printf("command:[%s]\n", command->command);
	printf("arg:[%s]\n", command->arg);
	printf("outfile:[%s]\n", command->outfile);
	return (0);
}
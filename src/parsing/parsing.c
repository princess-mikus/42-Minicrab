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

char	*rsearch_alpha(char *str) // search for the first non space caracter from end to beggining and returns it position //HAS TO BE CHANGED 
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

char	*search_alpha(char *str) // search for the next non space caracter and returns it position //HAS TO BE CHANGED 
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
int	next_is_file(char *str) //checks if the next caracter other than the space is a >|<
{
	int i;

	i  = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '<' || str[i] == '>')
			return (true);
		else if (str[i] != ' ')
			return (false);
		i++;
	}
	return (false);
}


void	new_arg(char *line, t_command *node)
{
	char *temp;

	if (search_alpha(line) == NULL) //bastante seguro de que esto sobra pero who knows
		return ;
	if (ft_strchr(line, '>')) // if a outfile exist the arg goes until the '>' whiout trimming the spaces
	{
		temp = ft_substr(line, 0, (ft_strchr(line, '>')) - line);
		node->arg = ft_strtrim(temp, " ");
		free(temp);
	}
	else if (ft_strchr(line, '<')) // if a infile exist the arg goes until the '<' whiout trimming the spaces
	{
		temp = ft_substr(line, 0, (ft_strchr(line, '<')) - line);
		node->arg = ft_strtrim(temp, " ");
		free(temp);
	}
	else //if the arg is the last thing in the line it trimmes the spaces at the end
		node->arg = ft_strtrim(line, " ");
	if (ft_strlen(node->arg) == 0) // under circunstances i dont remenber the trimming can produce a empty line of size 1, erase it
	{
		free(node->arg);
		node->arg = NULL;
	}
}
int	new_cmd(char *line, t_command *node)
{
	if (ft_strchr(line, ' ') - line < ft_strchr(line, '<') - line
	|| ft_strchr(line, ' ') - line < ft_strchr(line, '>') - line
	|| !ft_strchr(line, '>') || !ft_strchr(line, '<')) //the command ist the end of the line, there is a ' ' just after it
	{
		node->command = ft_substr(line, 0, ft_strchr(line, ' ') - line);
		return (ft_strchr(line, ' ') - line);
	}
	if (ft_strchr(line, '<')) //the < if abjacent to the comand whit no spaces in betewn
		node->command = ft_substr(line, 0, ft_strchr(line, '<') - line);
	else if (ft_strchr(line, '>')) //the > if abjacent to the comand whit no spaces in betewn
		node->command = ft_substr(line, 0, ft_strchr(line, '>') - line);
	else //the command is the end of the line
		node->command = ft_substr(line, 0, ft_strlen(line));
	return (ft_strlen(line));
}

int	get_offset(char *line, char c)
{
	if (line[0] == c)
	{
		if (line[0] == c && (!ft_strchr(line, ' ')
			|| (!ft_strchr(search_alpha(line + 1), ' ')))) // the file is the only part of the line
			return (ft_strlen(line));
		if (next_is_file(ft_strchr(line, ' ')) || 
		next_is_file(ft_strchr(search_alpha(line + 1), ' '))) //the infile and the outfile are the only parts of the line
			return (ft_strlen(line));
		if (line[0] == c  && ft_strchr(search_alpha(
			ft_strchr(line, c)), ' ') && line[1] == ' ') // the file is at the beggining and there are spaces betwen the >|< and the filename
			return (search_alpha(ft_strchr(
				search_alpha(line + 1), ' ')) - line);
		else if (line[0] == c  && ft_strchr(
			search_alpha(ft_strchr(line, c)), ' ')) // the file is at the beggining and there are not spaces betwen the >|< and the filename
			return (search_alpha(ft_strchr(line, ' ')) - line);
		printf("check : %d\n", next_is_file(ft_strchr(search_alpha(line + 1), ' ')));
	}
	return (0); //the file is at the end of the line
}

int	new_outfile(char *line, t_command *node)
{
	if (ft_strchr(line, '>') && ft_strchr(search_alpha(
		ft_strchr(line, '>')), ' ') && ft_strchr(line, '>')[1] == ' ') // the outfile is at the beggining and there are spaces betwen the > and the filename
		node->outfile = ft_substr(line, search_alpha(line + 1) - line, 
		ft_strchr(search_alpha(line + 1), ' ') - search_alpha(line + 1));
	else if (ft_strchr(line, '>') && ft_strchr(
		search_alpha(ft_strchr(line, '>')), ' ')) // the outfile is at the beggining and there are not spaces betwen the > and the filename
		node->outfile = ft_substr(line, 1, ft_strchr(line, ' ') - line - 1);
	else if (ft_strchr(line, '>') && ft_strchr(line, '>')[1] == ' ')  // the outfile is at the end and there are spaces betwen the > and the filename
		node->outfile = ft_substr(line,
			search_alpha(ft_strchr(line, '>')) - line,
			ft_strlen(search_alpha(ft_strchr(line, '>'))));	
	else if (ft_strchr(line, '>'))// the outfile is at the end and there are not spaces betwen the > and the filename
		node->outfile = ft_substr(line,
			ft_strchr(line, '>') - line + 1,
			ft_strlen(search_alpha(ft_strchr(line, '>'))));
	return (get_offset(line ,'>'));
}
int	new_infile(char *line, t_command *node)
{
	if (ft_strchr(line, '<') && ft_strchr(search_alpha(
		ft_strchr(line, '<')), ' ') && ft_strchr(line, '<')[1] == ' ') // the infile is at the beggining and there are spaces betwen the < and the filename
		node->infile = ft_substr(line, search_alpha(line + 1) - line, 
		ft_strchr(search_alpha(line + 1), ' ') - search_alpha(line + 1));
	else if (ft_strchr(line, '<') && ft_strchr(
		search_alpha(ft_strchr(line, '<')), ' ')) // the infile is at the beggining and there are not spaces betwen the < and the filename
		node->infile = ft_substr(line, 1, ft_strchr(line, ' ') - line - 1);
	else if (ft_strchr(line, '<') && ft_strchr(line, '<')[1] == ' ')  // the infile is at the end and there are spaces betwen the < and the filename
		node->infile = ft_substr(line,
			search_alpha(ft_strchr(line, '<') + 1) - line,
			ft_strlen(search_alpha(ft_strchr(line, '<') + 1)));	
	else if (ft_strchr(line, '<'))// the infile is at the end and there are not spaces betwen the < and the filename
		node->infile = ft_substr(line,
			ft_strchr(line, '<') - line + 1,
			ft_strlen(search_alpha(ft_strchr(line, '<'))));
	return (get_offset(line, '<'));
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
	if (line[offset] == '<' || line[offset] == '>' || !search_alpha(line + offset))
		return (new);
	offset += new_cmd(line + offset, new);
	new_arg(line + offset, new);
	return (new);
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
	char	*trim;
	int		i;

	splited = ft_split(line_expanded, '|');
	i = 0;
	while (splited[i])
	{
		trim = ft_strtrim(splited[i], " ");
		add_command(trim, commands);
		free(trim);
		i++;
	}
}

int main(int argc, char **argv)
{
	//./minishell "<   in ls -l a   >    out   |   <   out  cat -l>    in | aaaaa aaa"
	//char *line = "   >    outfile    ls  < infile ";
	//char *line = "  <     infile    ls    -l   a    >    outfile";
	//char *line = "   > o    l    a  u  < i ";
	//char *line = " <      infile    ls   -la    ";
	//char *line = " ls -la  > outfile";
	//char *line = " >outfile    <infile";
	//char *line = " >   outfile    <   infile";
	//char *line = " >o <i";
	//char *line = " >  o <  i";
	//char *line = " ls -la ";
	//char *line = " ls -l     a ";
	//char *line = " ls ";
	t_command *command;
	if (argc < 2)
		return (0);

	command = NULL;
	parse(argv[1], &command);
	//command = new_command(line);
	
	printf("line:[%s]\n", argv[1]);
	while (command)
	{
		printf("-----------------------------------------\n");
		printf("infile:[%s]\n", command->infile);
		printf("command:[%s]\n", command->command);
		printf("arg:[%s]\n", command->arg);
		printf("outfile:[%s]\n", command->outfile);
		command = command->next;
	}
	printf("-----------------------------------------\n");
	return (0);
}
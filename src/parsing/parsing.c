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

char	*jmp_spaces(char *str)
{
	int i;

	i  = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (str + i);
		i++;
	}
	return (NULL);
}

char *search_out_quotes(char *line, char c)
{
	int i;
	int status;

	i = 0;
	status = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			status++;
		if (line[i] == c && status % 2 == 0)
		{
			return (line + i);
		}
		i++;
	}
	return (NULL);
}

char *line_cutter(char *line, char *to_cut)
{
    char	*new_line;
	 char	*part_1;
	 char	*part_2;
	 int	start;
	 int	end;

    if (to_cut && line)
    {
		start = ft_strnstr(line, to_cut, ft_strlen(line)) - line;
		end = ft_strlen(to_cut);
		part_1 = ft_substr(line, 0, start);
		part_2 = ft_substr(line, start + end, ft_strlen(line) - (end + start));
		new_line = ft_strjoin(part_1, part_2);
		free(line);
		free(part_1);
		free(part_2);
		return(new_line);
    }
	return(line);
}

char *get_outfile(char *line, t_command *node)
{
	int	start;
	int	end;
	char	*temp;

	if (!search_out_quotes(line, '>'))
		return(line);
	start = jmp_spaces(search_out_quotes(line, '>')) - line;
	if (line[start + 1 + node->apend] == '"')
		end = ft_strchr(ft_strchr(line + start + 2 + node->apend, '"'), ' ') - line;
	else
		end = ft_strchr(line + start + 1, ' ') - line;
	temp = ft_substr(line, start, end - start);
	if (search_out_quotes(temp, '<'))
		node->outfile = ft_substr(temp, 0, search_out_quotes(temp, '<') - temp);
	else
		node->outfile = ft_strdup(temp);
	free(temp);
	return(line_cutter(line, node->outfile));
}
char *get_infile(char *line, t_command *node)
{
	int	start;
	int	end;
	char	*temp;

	if (!search_out_quotes(line, '<'))
		return(line);
	start = jmp_spaces(search_out_quotes(line, '<')) - line;
	if (line[start + 1 + node->hdoc] == '"')
		end = ft_strchr(ft_strchr(line + start + 2 + node->hdoc, '"'), ' ') - line;
	else
		end = ft_strchr(line + start + 1, ' ') - line;
	temp = ft_substr(line, start, end - start);
	if (search_out_quotes(temp, '>'))
		node->infile = ft_substr(temp, 0, search_out_quotes(temp, '>') - temp);
	else
		node->infile = ft_strdup(temp);
	free(temp);
	return(line_cutter(line, node->infile));
}

void	init_node(t_command *node)
{
	node->apend = 0;
	node->hdoc = 0;
	node->infile = NULL;
	node->outfile = NULL;
	node->dec = NULL;
	node->command = NULL;
	node->arg = NULL;
	node->next = NULL;
}

t_command *new_command(char *line)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	init_node(new);
	if (search_out_quotes(line, '<') && search_out_quotes(line, '<')[1] == '<')
		new->hdoc = 1;
	if (search_out_quotes(line, '>') && search_out_quotes(line, '>')[1] == '>')
		new->apend = 1;
   line = get_infile(line, new);
   printf("line after infile [%s]\n", line);
   line = get_outfile(line, new);
   printf("line after outfile [%s]\n", line);
   //get_outfile(line, new);
   //get_declaration(line, new);
   //get_command(line, new);
   //get_argument(line, new);
	return (new);
}

void	add_command(char *line_splited, t_command **commands)
{
	t_command	*current;

	current = *commands;
	if (!current)
		*commands = new_command(line_splited);
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_command(line_splited);
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

int main(void)//int argc, char **argv
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
	char *line = ft_strdup("<<\"ho  \"la>>\"que tal\"");
	//line = line_cutter(line, "que");
	//printf("[%s]\n", line);
	t_command *command;
//	if (argc < 2)
//		return (0);
//
	command = NULL;
//	parse(argv[1], &command);
	command = new_command(line);
//	
	printf("line:[%s]\n", line);
	while (command)
	{
		printf("-----------------------------------------\n");
		printf("hdoc:[%d]\n", command->hdoc);
		printf("apend:[%d]\n", command->apend);
		printf("infile:[%s]\n", command->infile);
		printf("outfile:[%s]\n", command->outfile);
		//printf("dec:[%s]\n", command->dec);
		printf("command:[%s]\n", command->command);
		printf("arg:[%s]\n", command->arg);
		command = command->next;
	}
	printf("-----------------------------------------\n");
	return (0);
}
//no funcia un solo infile/outfile ni solo infile y outfile
//checkea si se puede poner < infile > outfile comando args

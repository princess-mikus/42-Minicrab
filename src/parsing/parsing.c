/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:35:43 by xortega           #+#    #+#             */
/*   Updated: 2024/06/10 12:44:32 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_dec(char *line)
{
	int	i;

	i = search_out_quotes(line, '=') - line;
	while (i > 0 && line[i] != ' ')
		i--;
	if (i > 0)
		i++;
	return (i);
}

t_file	**make_files(char *line, char c)
{
	t_file	**vector;
	int		n;

	if (count_out_quotes(line, c) != 0)
	{
		n = c_out_q_no_d(line, c);
		if (c == '=')
			n = count_out_quotes(line, c);
		vector = malloc(sizeof(t_file *) * (n + 1));
		vector[n] = NULL;
		while (n > 0)
			vector[--n] = malloc(sizeof(t_file));
	}
	else
		vector = NULL;
	return (vector);
}

void	init_node(t_command *node, char *line)
{
	node->infile = make_files(line, '<');
	node->outfile = make_files(line, '>');
	node->dec = make_files(line, '=');
	int		start;
	int		end;
	char	*temp;

	if (!search_out_quotes(line, '<'))
		return (line);
	start = search_out_quotes(line, '<') - line;
	if (jmp_spaces(line + start + node->hdoc + 1)[0] == '"')
		end = ft_strchr(ft_strchr(jmp_spaces(line + start + node->hdoc + 2) + 1, '"'), ' ') - line;
	else
		end = ft_strchr(jmp_spaces(line + start + node->hdoc + 1), ' ') - line;
	temp = ft_substr(line, start, end - start);
	if (search_out_quotes(temp, '>'))
		node->infile = ft_substr(temp, 0, search_out_quotes(temp, '>') - temp);
	else
		node->infile = ft_strdup(temp);
	free(temp);
	return (line_cutter(line, node->infile));
}

void	init_node(t_command *node)
{
	node->apend = 0;
	node->hdoc = 0;
	node->status = 0;
	node->infile = NULL;
	node->outfile = NULL;
	node->dec = NULL;
	node->command = NULL;
	node->arg = NULL;
	node->path = NULL;
	node->next = NULL;
}

t_command	*new_command(char *line)
{
	t_command	*new;
	int			i;

	new = malloc(sizeof(t_command));
	init_node(new, line);
	i = -1;
	while (search_out_quotes(line, '<'))
		line = get_infile(line, &new->infile[++i]->name);
	i = -1;
	while (search_out_quotes(line, '>'))
		line = get_outfile(line, &new->outfile[++i]->name);
	line = get_dec(line, new);
	line = get_cmd(line, new);
	if (!jmp_spaces(line))
		free(line);
	else
		get_arg(line, new);
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


char **trim_array(char** array, char *c)
{
	char	**trimed;
	int		i;

	i = 0;
	while (array[i])
		i++;
	trimed = malloc(sizeof(char *) * i);
	i = 0;
	while (array[i])
	{
		trimed[i] = ft_strtrim(array[i], c);
		i++;
	}
	trimed[i] = NULL;
	free_array((void **)array);
	return(trimed);

}

char **split_out_of_q(char* str, char c)
{
	char	**splited;
	int		i;
	int		j;
	int		k;

	splited = ft_calloc(sizeof(char *), count_out_quotes(str, c) + 2);
	splited[count_out_quotes(str, c) + 1] = NULL;
	i = 0;
	j = 0;
	k = 0;
	while(str[i])
	{
		if (is_out_quotes(str, i, c))
		{
			splited[k] = ft_substr(str, j, (i - 1) - j);
			k++;
			i = i + 1;
			j = i;
		}
		else
			i++;
		if (!str[i])
			splited[k] = ft_strdup(str + j);
	}
	return(splited);
}

/*
char **split_out_of_q(char *str, char c)
{
	char	**splitted;
	bool	s_quotes;
	bool	d_quotes;
	int		i;
	int		j;
	int		k;

	splitted = malloc((count_out_quotes(str, c) + 2) * sizeof(char *));
	s_quotes = false;
	d_quotes = false;
	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d_quotes ^= 1;
		if (str[i] == '\'')
			s_quotes ^= 1;
		if (str[i] == '|' && !d_quotes && !s_quotes)
		{
			splitted[k] = ft_substr(str, j, i - 1);
			i++;
			j = i;
			k++;
		}
		else
			i++;
	}
	return (splitted);
}
*/
void	parse(char *line_expanded, t_command **commands)
{
	char	**splited;
	char	*trim;
	int		i;

	if (search_out_quotes(line_expanded, '|'))
		splited = split_out_of_q(line_expanded, '|');
	else
	{
		splited = malloc(sizeof(char *) * 2);
		splited[0] = ft_strdup(line_expanded);
		splited[1] = NULL;
	}
	int j = -1;
	while (splited[++j])
		ft_printf("He salido en [%d] [%s]\n", j, splited[j]);
	i = 0;
	while (splited[i])
	{
		trim = ft_strtrim(splited[i], " ");
		add_command(trim, commands);
		i++;
	}
	free_array((void **)splited);
}

/*
int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	char *line = ft_strtrim(argv[1], " ");
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
	//char *line = ft_strtrim("<    in\"  file\"57 l\"s\"a -l\" a\"> \" jiji\"jija", " ");
	//char *line = ft_strtrim("<    in\"  file\"57 ", " ");
	//line = line_cutter(line, "que");
	//printf("[%s]\n", line);
	t_command *command;
	int i = -1;
//	if (argc < 2)
//		return (0);
//
	command = NULL;
	parse(line, &command);
    printf("line: [%s]\n", line);
//	command = new_command(line);
	cleaning(command);
	t_command *head = command;
	while (command)
	{
		i = -1;
		printf("-----------------------------------------\n");
		if(command->infile)
			while (command->infile[++i])
			{
				ft_printf("infile:[%s][%d]\n", command->infile[i]->name, command->infile[i]->special);

			}
		else
			ft_printf("infile:[(null)]\n");
		i = -1;
		if(command->outfile)
			while (command->outfile[++i])
				ft_printf("outfile:[%s][%d]\n", command->outfile[i]->name, command->outfile[i]->special);
		else
			ft_printf("outfile:[(null)]\n");
		i = -1;
		if (command->dec)
			while (command->dec[++i])
				ft_printf("declaration %d:[%s][%d]\n", i, command->dec[i]->name, command->dec[i]->special);
		else
			ft_printf("declaration:[(null)]\n");
		ft_printf("command:[%s]\n", command->command);
		i = -1;
		if (command->argv)
			while(command->argv[++i])
				ft_printf("argv[%d]:[%s]\n", i, command->argv[i]);
		ft_printf("arg:[%s]\n", command->arg);
		command = command->next;
	}
	printf("-----------------------------------------\n");
	free(line);
	free_command_list(&head);
	//ft_printf("%s\n", line]);
	//ft_printf("%d\n", quote_case(line));
	//ft_printf("%s\n", clear_line(line));
	return (0);
}*/

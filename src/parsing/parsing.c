/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:35:43 by xortega           #+#    #+#             */
/*   Updated: 2024/06/03 10:53:45 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_case(char *line)
{
	int	i;
	int	status_1;
	int	status_2;

	i = 0;
	status_1 = 0;
	status_2 = 0;
	while (line[i])
	{
		if (line[i] == '\"' && status_2 % 2 == 0)
			status_1++;
		if (line[i] == '\'' && status_1 % 2 == 0)
			status_2++;
		if (status_1 == 2)
			return(1);
		if (status_2 == 2)
			return(2);
		i++;
	}
	return (0);
}

char *clear_line(char *str)
{
	char	*retu;
	char	*start;
	char	*mid;
	char	*end;
	char	c;

	//nada que limpiar (no hay " ' pares)
	if (!quote_case(str))
		return(str);
	c = '\'';
	if (ft_strchr(str, '"') &&
	ft_strchr(str, '"') < ft_strchr(str, '\''))
		c = '"';
	start = ft_substr(str, 0, ft_strchr(str, c) - str);
	mid = ft_substr(str, ft_strchr(str, c) - str, ft_strrchr(str, c) - str);
	end = ft_substr(str, ft_strrchr(str, c) - str + 1, 
	ft_strlen(ft_strrchr(str, c)));
	retu = ft_strtrim(mid, &c);
	free(mid);
	mid = retu;
	retu = ft_strjoin(start, mid);
	free(mid);
	mid = retu;
	retu = ft_strjoin(mid, end);
	return(free(start), free(mid), free(end), retu);
}

int	start_dec(char *line)
{
	int	i;

	i = search_out_quotes(line, '=') - line;
	while (line[i] != ' ' && i > 0)
		i--;
	if (i > 0)
		i++;
	return (i);
}

t_file	**make_files(char *line, char c)
{
	t_file	**vector;
	int	n;

	if (count_out_quotes(line, c) != 0)
	{
		n = c_out_q_no_d(line, c);
		vector = malloc(sizeof(t_file *) * (n + 1));
		vector[n] = NULL;
		while (n > 0)
			vector[--n] = malloc(sizeof(t_file));
	}
	else
		vector = NULL;
	return(vector);
}

void	init_node(t_command *node, char * line)
{
	node->infile = make_files(line, '<');
	node->outfile = make_files(line, '>');
	node->dec = make_files(line, '=');
	node->command = NULL;
	node->arg = NULL;
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
	if(ft_strlen(line) == 0)
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
		//free(trim);
		i++;
	}
}


int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
/*	//./minishell "<   in ls -l a   >    out   |   <   out  cat -l>    in | aaaaa aaa"
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
	char *line = ft_strtrim(argv[1], " ");
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
	printf("-----------------------------------------\n");*/
	ft_printf("%s\n", argv[1]);
	ft_printf("%d\n", quote_case(argv[1]));
	ft_printf("%s\n", clear_line(argv[1]));
	return (0);
}

//creo que los outfiles e infiles despues del comando joden el arg pero no se porque
//no pilla las comiilas dobles o simples en las declaraciones
/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parsing.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mikus <mikus@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/10 10:29:05 by xortega		   #+#	#+#			 */
/*   Updated: 2024/05/16 20:57:28 by mikus			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

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

t_command	*new_command(char *line)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	init_node(new);
	if (search_out_quotes(line, '<') && search_out_quotes(line, '<')[1] == '<')
		new->hdoc = 1;
	if (search_out_quotes(line, '>') && search_out_quotes(line, '>')[1] == '>')
		new->apend = 1;
	line = get_infile(line, new);
	line = get_outfile(line, new);
	line = get_dec(line, new);
	line = get_cmd(line, new);
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
	char *line = ft_strdup("<< \"in  fi\"le>>  out_file \"com \"ando c=uno b=\"do s   \" c=uno2 b=\" tre \"s soy \"el argu\" mento");
	//char *line = ft_strtrim("<    in\"  file\"57 l\"s\"a -l\" a\"> \" jiji\"jija", " ");
	//char *line = ft_strtrim("<    in\"  file\"57 ", " ");
	//line = line_cutter(line, "que");
	//printf("[%s]\n", line);
	t_command *command;
//	if (argc < 2)
//		return (0);
//
	command = NULL;
//	parse(argv[1], &command);
    printf("line: [%s]\n", line);
	command = new_command(line);
    cleaning(command);
	int i = -1;
	while (command)
	{
		printf("-----------------------------------------\n");
		printf("hdoc:[%d]\n", command->hdoc);
		printf("apend:[%d]\n", command->apend);
		printf("infile:[%s]\n", command->infile);
		printf("outfile:[%s]\n", command->outfile);
		if (command->dec)
			while (command->dec[++i])
				printf("declaration %d:[%s]\n", i, command->dec[i]);
		printf("command:[%s]\n", command->command);
		printf("arg:[%s]\n", command->arg);
		command = command->next;
	}
	printf("-----------------------------------------\n");
	return (0);
}

//el end de los substrings va a fallar sin espacio al final, asi que arreglalo
//las declaraciones de tipo b="ho"la tambien van mal
// si el infile|outfile tieene > out"  file" no va
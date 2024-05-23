/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:35:43 by xortega           #+#    #+#             */
/*   Updated: 2024/05/23 10:41:25 by xortega          ###   ########.fr       */
/*                                                                            */
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


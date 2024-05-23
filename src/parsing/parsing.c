/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:40:10 by mikus             #+#    #+#             */
/*   Updated: 2024/05/23 21:40:36 by mikus            ###   ########.fr       */
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

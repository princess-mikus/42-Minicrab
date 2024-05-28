/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:48 by codespace         #+#    #+#             */
/*   Updated: 2024/05/27 09:42:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clean_dec(t_command *node)
{
	int i;
	
	if(!node->dec || !node->dec[0])
		return ;
	i = 0;
	while (node->dec[i])
	{
		ft_printf("%s\n", node->dec[i]->name);
		while (strchr(node->dec[i]->name, '"'))
		{
			node->dec[i]->name = line_cutter(node->dec[i]->name, "\"");
			node->dec[i]->special = 0;
		}
		i++;
	}
}

void clean_command_arg(t_command *node)
{
	if (node->arg)
		while (strchr(node->arg, '"'))
			node->arg = line_cutter(node->arg, "\"");
	if (node->command)
		while (strchr(node->command, '"'))
			node->command = line_cutter(node->command, "\"");
}

void clean_outfile(t_command *node)
{
	char	*temp;
	int		start;
	int		i;

	if (!node->outfile)
		return ;
	i = 0;
	while (node->outfile[i])
	{
		if(node->outfile[i]->name[1] == '>')
			node->outfile[i]->special = 1;		
		if (ft_strlen(node->outfile[i]->name) > 2)
			start = jmp_spaces(node->outfile[i]->name + 1 +
				node->outfile[i]->special) - node->outfile[i]->name;
		else
			start = 1 + node->outfile[i]->special;
		temp = ft_strdup(node->outfile[i]->name + start);
		while (strchr(temp, '"'))
			temp = line_cutter(temp, "\"");
		free(node->outfile[i]->name);
		node->outfile[i]->name = temp;
		i++;
	}
}

void clean_infile(t_command *node)
{
	char	*temp;
	int		start;
	int		i;

	if (!node->infile)
		return ;
	i = 0;
	while (node->infile[i])
	{
		if(node->infile[i]->name[1] == '<')
			node->infile[i]->special = 1;		
		if (ft_strlen(node->infile[i]->name) > 2)
			start = jmp_spaces(node->infile[i]->name + 1 +
            node->infile[i]->special) - node->infile[i]->name;
		else
			start = 1 + node->infile[i]->special;
		temp = ft_strdup(node->infile[i]->name + start);
		while (strchr(temp, '"'))
			temp = line_cutter(temp, "\"");
		free(node->infile[i]->name);
		node->infile[i]->name = temp;
		i++;
	}
}

void	cleaning(t_command *node)
{
	clean_infile(node);
	clean_outfile(node);
	clean_command_arg(node);
	clean_dec(node);
}

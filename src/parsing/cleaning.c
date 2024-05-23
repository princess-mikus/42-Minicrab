/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:48 by codespace         #+#    #+#             */
/*   Updated: 2024/05/17 12:46:50 by codespace        ###   ########.fr       */
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
		while (strchr(node->dec[i], '"'))
			node->dec[i] = line_cutter(node->dec[i], "\"");
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

	if (!node->outfile)
		return ;
	start = jmp_spaces(node->outfile + 1 + node->apend) - node->outfile;
	temp = ft_strdup(node->outfile + start);
	while (strchr(temp, '"'))
		temp = line_cutter(temp, "\"");
	free(node->outfile);
	node->outfile = temp;
}

void clean_infile(t_command *node)
{
	char	*temp;
	int		start;

	if (!node->infile)
		return ;
	
	start = jmp_spaces(node->infile + 1 + node->hdoc) - node->infile;
	temp = ft_strdup(node->infile + start);
	while (strchr(temp, '"'))
		temp = line_cutter(temp, "\"");
	free(node->infile);
	node->infile = temp;
}

void	cleaning(t_command *node)
{
	clean_infile(node);
	clean_outfile(node);
	clean_command_arg(node);
	clean_dec(node);
}

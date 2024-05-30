/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:48 by codespace         #+#    #+#             */
/*   Updated: 2024/05/30 18:50:44 by xortega          ###   ########.fr       */
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
		while (ft_strchr(node->dec[i]->name, '"'))
		{
			node->dec[i]->name = line_cutter(node->dec[i]->name, "\"");
			node->dec[i]->special = 0;
		}
		i++;
	}
}

int get_end(char *line, char c)
{
	if (c == '"')
		return (ft_strchr(line + 1, '"') - line);
	
}

void clean_command_arg(t_command *node)
{
	int		words;
	int		start;
	int		end;
	int		i;

	if (node->arg)
	{
		words = c_out_q_no_d(node->arg, ' ') + 1;
		node->argv = malloc((sizeof(char*)) * words + 1);
		i = 0;
		while (i < words)
		{
			end = get_end(node->arg, node->arg[0]);
			node->argv[i] = ft_substr(node->arg, start, end - start);
			line_cutter(node->arg, node->argv[i]);
			i++;
		}
		node->argv[i] = NULL;
		
	}
	if (node->command)
		while (ft_strchr(node->command, '"'))
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
		while (ft_strchr(temp, '"'))
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
			start = node->infile[i]->special + 1;
		temp = ft_strdup(node->infile[i]->name + start);
		while (ft_strchr(temp, '"'))
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

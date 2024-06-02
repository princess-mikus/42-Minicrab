/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:48 by codespace         #+#    #+#             */
/*   Updated: 2024/06/02 20:08:37 by mikus            ###   ########.fr       */
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

int get_arg_end(char *line, char c)
{
	if (c == '"')
	{
		if (ft_strchr(ft_strchr(line + 1, '"'), ' '))
			return(ft_strchr(ft_strchr(line + 1, '"'), ' ') - line);
		return (ft_strchr(line + 1, '"') - line + 1);
	}
	if (c == '\'')
	{
		if (ft_strchr(ft_strchr(line + 1, '\''), ' '))
			return(ft_strchr(ft_strchr(line + 1, '\''), ' ') - line);
		return (ft_strchr(line + 1, '\'') - line + 1);
	}
	if (ft_strchr(line, ' '))
		return(ft_strchr(line, ' ') - line);
	return(ft_strlen(line));
}

void divide_arg(t_command *node)
{
	int		words;
	int		end;
	int		i;
	char	*temp;

	words = c_out_q_no_d(node->arg, ' ') + 1;
	node->argv = malloc((sizeof(char*)) * words + 1);
	i = 0;
	while (ft_strlen(node->arg) > 0)
	{
		end = get_arg_end(node->arg, node->arg[0]);
		node->argv[i] = ft_substr(node->arg, 0, end);
		node->arg = line_cutter(node->arg, node->argv[i]);
		temp = ft_strtrim(node->arg, " ");
		free(node->arg);
		node->arg = temp;
		i++;
	}
	node->argv[i] = NULL;
	i = 0;
	free(node->arg);
	node->arg = NULL;
}
void clean_arg(t_command *node)
{
	int		i;
	char	c;
	char	*temp;

	if (node->arg)
	{
		divide_arg(node);
		i = 0;
		while(node->argv[i])
		{
			c = node->argv[i][0];
			if (c == '\'' || c == '"')
			{
				temp = ft_strtrim(node->argv[i], &c);
				free(node->argv[i]);
				node->argv[i] = temp;
			}
			i++;
		}
	}
	else
		node->argv = NULL;
}
void clean_command(t_command *node)
{
	char	c;
	char	*temp;
	if (node->command)
	{
		c = node->command[0];
		if (c == '\'' || c == '"')
		{
			if (ft_strlen(node->command) <= 2)
			{
				free(node->command);
				node->command = NULL;
			}
				return ;
			temp = ft_strtrim(node->command, &c);
			free(node->command);
			node->command = temp;
		}
	}
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
	clean_command(node);
	clean_arg(node);
	clean_dec(node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:48 by codespace         #+#    #+#             */
/*   Updated: 2024/06/07 14:45:36 by xortega          ###   ########.fr       */
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
			return (1);
		if (status_2 == 2)
			return (2);
		i++;
	}
	return (0);
}

void	clean_dec(t_command *node)
{
	int		i;
	char	*temp;

	if (!node->dec || !node->dec[0])
		return ;
	i = 0;
	while (node->dec[i])
	{
		temp = ft_strtrim(node->dec[i]->name, " ");
		free(node->dec[i]->name);
		node->dec[i]->name = make_line(temp);
		i++;
	}
}

int	get_arg_end(char *line, char c)
{
	if (c == '"')
	{
		if (ft_strchr(ft_strchr(line + 1, '"'), ' '))
			return (ft_strchr(ft_strchr(line + 1, '"'), ' ') - line);
		return (ft_strlen(line));
	}
	if (c == '\'')
	{
		if (ft_strchr(ft_strchr(line + 1, '\''), ' '))
			return (ft_strchr(ft_strchr(line + 1, '\''), ' ') - line);
		return (ft_strlen(line));
	}
	if (ft_strchr(line, ' '))
		return (ft_strchr(line, ' ') - line);
	return (ft_strlen(line));
}

void	divide_arg(t_command *node)
{
	int		words;
	int		end;
	int		i;
	char	*temp;

	words = c_out_q_no_d(node->arg, ' ') + 1;
	node->argv = malloc((sizeof(char *)) * words + 1);
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
	free(node->arg);
	node->arg = NULL;
}

void	clean_arg(t_command *node)
{
	int		i;

	if (node->arg)
	{
		divide_arg(node);
		i = 0;
		while (node->argv[i])
		{
			node->argv[i] = make_line(node->argv[i]);
			i++;
		}
	}
	else
		node->argv = NULL;
}
void	clean_command(t_command *node)
{
	if (node->command)
		node->command = make_line(node->command);
}

void	clean_outfile(t_command *node)
{
	int		i;
	char	*temp;

	if (!node->outfile)
		return ;
	i = 0;
	while (node->outfile[i])
	{
		node->outfile[i]->special = 0;
		if (node->outfile[i]->name[1] == '>')
			node->outfile[i]->special = 1;
		temp = ft_strtrim(node->outfile[i]->name
				+ node->outfile[i]->special + 1, " ");
		free(node->outfile[i]->name);
		node->outfile[i]->name = make_line(temp);
		i++;
	}
}

void	clean_infile(t_command *node)
{
	int		i;
	char	*temp;

	if (!node->infile)
		return ;
	i = 0;
	while (node->infile[i])
	{
		node->infile[i]->special = 0;
		if (node->infile[i]->name[1] == '<')
			node->infile[i]->special = 1;
		temp = ft_strtrim(node->infile[i]->name
				+ node->infile[i]->special + 1, " ");
		free(node->infile[i]->name);
		node->infile[i]->name = make_line(temp);
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

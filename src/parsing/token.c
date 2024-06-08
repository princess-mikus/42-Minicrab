/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:15:06 by xortega           #+#    #+#             */
/*   Updated: 2024/06/08 17:02:59 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_arg(char *line, t_command *node)
{
	if (!line)
		return ;
	node->arg = ft_strtrim(line, " ");
	free(line);
}

char	*get_cmd(char *line, t_command *node)
{
	int	start;
	int	end;

	if (!line || !jmp_spaces(line))
		return (line);
	start = jmp_spaces(line) - line;
	if (search_out_quotes(line + start, ' '))
		end = (search_out_quotes(line + start, ' ') - line);
	else
		end = ft_strlen(line);
	node->command = ft_substr(line, start, end - start);
	return (line_cutter(line, node->command));
}

char	*get_dec(char *line, t_command *node)
{
	int	i;
	int	start;
	int	end;

	if (count_out_quotes(line, '=') == 0)
		return (line);
	i = 0;
	while (line && count_out_quotes(line, '=') > 0)
	{
		start = start_dec(line);
		if (search_out_quotes(search_out_quotes(line, '='), ' '))
			end = (search_out_quotes(search_out_quotes(line, '='), ' ') - line);
		else
			end = ft_strlen(line);
		node->dec[i]->name = ft_substr(line, start, end - start);
		line = line_cutter(line, node->dec[i++]->name);
	}
	node->dec[i] = NULL;
	return (line);
}

int	logic(char *temp, char caso, char other)
{
	if (search_out_quotes(temp, caso))
	{
		if (search_out_quotes(temp, other)
			&& (search_out_quotes(temp, other)
				< search_out_quotes(temp, caso)))
			return (false);
		return (true);
	}
	return (false);
}

char	*get_outfile(char *line, char **outfile)
{
	int		start;
	int		end;
	char	*temp;

	if (!search_out_quotes(line, '>'))
		return (line);
	start = search_out_quotes(line, '>') - line;
	end = 0;
	if (ft_strlen(line + start) > 2)
		end = jmp_spaces(line + start + (line[start + 1] == '>') + 1) - line;
	if (search_out_quotes(line + end, ' '))
		end = (search_out_quotes(line + end, ' ') - line);
	else
		end = ft_strlen(line);
	temp = ft_substr(line, start, end - start);
	if (logic(temp + 2, '<', '>'))
		*outfile = ft_substr(temp, 0, search_out_quotes(temp, '<') - temp);
	else if (logic(temp + 2, '>', '<'))
		*outfile = ft_substr(temp, 0, search_out_quotes(temp + 2, '>') - temp);
	else
		*outfile = ft_strdup(temp);
	free(temp);
	return (line_cutter(line, *outfile));
}

char	*get_infile(char *line, char **infile)
{
	int		start;
	int		end;
	char	*temp;

	if (!search_out_quotes(line, '<'))
		return (line);
	start = search_out_quotes(line, '<') - line;
	end = 0;
	if (ft_strlen(line + start) > 2)
		end = jmp_spaces(line + start + (line[start + 1] == '<') + 1) - line;
	if (search_out_quotes(line + end, ' '))
		end = (search_out_quotes(line + end, ' ') - line);
	else
		end = ft_strlen(line);
	temp = ft_substr(line, start, end - start);
	if (logic(temp + 2, '>', '<'))
		*infile = ft_substr(temp, 0, search_out_quotes(temp, '>') - temp);
	else if (logic(temp + 2, '<', '>'))
		*infile = ft_substr(temp, 0, search_out_quotes(temp + 2, '<') - temp);
	else
		*infile = ft_strdup(temp);
	free(temp);
	return (line_cutter(line, *infile));
}

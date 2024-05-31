/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:15:20 by xortega           #+#    #+#             */
/*   Updated: 2024/05/31 11:09:59 by xortega          ###   ########.fr       */
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
	end = start;
	if (line[start] == '"')
		end = (ft_strchr(line + start + 1, '"') - line) + 1;
    if (ft_strchr(line + start, ' '))
        end = ft_strchr(line + end, ' ') - line;
    else
    {
        end = ft_strlen(line);
    }
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
	while (count_out_quotes(line, '=') > 0)
	{
		start = start_dec(line);
		if (search_out_quotes(line, '=')[1] == '"')
		{
			if (ft_strchr(ft_strchr(search_out_quotes(line, '=') + 2, '"'), ' '))
				end = (ft_strchr(ft_strchr(search_out_quotes(line, '=') + 2, '"'), ' ') - line);
			else
				end = ft_strlen(search_out_quotes(line, '=') - 1);
		}
		else
			end = ft_strchr(search_out_quotes(line, '='), ' ') - line;
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
		if (search_out_quotes(temp, other) && 
		search_out_quotes(temp, other) <
		search_out_quotes(temp, caso))
			return (false);
		return (true);
	}
	return (false);
}

int	get_end(char *line, int end)
{
	if (line[end] == '"')
		end = ft_strchr(line + end + 1, '"') - line;
	else if (ft_strchr(line + end, '"') && ft_strchr(line + end, ' ')
	&& ft_strchr(line + end, '"') < ft_strchr(line + end, ' '))
		end = ft_strchr(ft_strchr(line + end, '"') + 2, '"') - line;
	if (line[end] == '\'')
		end = ft_strchr(line + end + 1, '\'') - line;
	else if (ft_strchr(line + end, '\'') && ft_strchr(line + end, ' ')
	&& ft_strchr(line + end, '\'') < ft_strchr(line + end, ' '))
		end = ft_strchr(ft_strchr(line + end, '\'') + 2, '\'') - line;
	return (end);
}
char	*get_outfile(char *line, char **outfile)
{
	int		start;
	int		end;
	char	*temp;

	if (!search_out_quotes(line, '>'))
		return (line);
	start = search_out_quotes(line, '>') - line;
	if (ft_strlen(line + start) > 2)
		end = jmp_spaces(line + start + 2) - line;
	else
		end = 0;
	end = get_end(line, end);
    if (ft_strchr(line + end, ' '))
        end = ft_strchr(line + end, ' ') - line;
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
	if (ft_strlen(line + start) > 2)
		end = jmp_spaces(line + start + 2) - line;
	else
		end = 0;
	end = get_end(line, end);
    if (ft_strchr(line + end, ' '))
        end = ft_strchr(line + end, ' ') - line;
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

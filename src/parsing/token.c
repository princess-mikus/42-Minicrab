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

void	get_arg(char *line, t_command *node)
{
	if (!line)
		return ;
	if (jmp_spaces(line))
		node->arg = ft_strdup(jmp_spaces(line));
	free(line);
}

char	*get_cmd(char *line, t_command *node)
{
	int	start;
	int	end;

	if (!line || !jmp_spaces(line))
		return (line);
    printf("antes de cmd [%s]\n", line);
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
	node->dec = malloc(sizeof(char *) * (count_out_quotes(line, '=') + 1));
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
		node->dec[i] = ft_substr(line, start, end - start);
		line = line_cutter(line, node->dec[i++]);
	}
	node->dec[i] = NULL;
	return (line);
}

char	*get_outfile(char *line, t_command *node)
{
	int		start;
	int		end;
	char	*temp;

	if (!search_out_quotes(line, '>'))
		return (line);
	start = search_out_quotes(line, '>') - line;
	if (jmp_spaces(line + start + node->apend + 1)[0] == '"')
		end = ft_strchr(jmp_spaces(line + start + node->apend + 2) + 1, '"') - line;
    else if (strchr(line + start, '"' && strchr(line + start, ' ')
    && strchr(line + start, '"') > strchr(line + start, ' ')))
        end = ft_strchr(ft_strchr(line + start, '"') + 1, '"') - line;
	else
		end = jmp_spaces(line + start + node->apend + 1) - line;
    if (ft_strchr(line + end, ' '))
        end = ft_strchr(line + end, ' ') - line;
    else
		end = ft_strlen(line);
	temp = ft_substr(line, start, end - start);
	if (search_out_quotes(temp, '>'))
		node->outfile = ft_substr(temp, 0, search_out_quotes(temp, '<') - temp);
	else
		node->outfile = ft_strdup(temp);
	free(temp);
	return (line_cutter(line, node->outfile));
}

char	*get_infile(char *line, t_command *node)
{
	int		start;
	int		end;
	char	*temp;

	if (!search_out_quotes(line, '<'))
		return (line);
	start = search_out_quotes(line, '<') - line;
	if (jmp_spaces(line + start + node->hdoc + 1)[0] == '"')
		end = ft_strchr(jmp_spaces(line + start + node->hdoc + 2) + 1, '"') - line;
    else if (strchr(line + start, '"' && strchr(line + start, ' ')
    && strchr(line + start, '"') > strchr(line + start, ' ')))
        end = ft_strchr(ft_strchr(line + start, '"') + 2, '"') - line;
	else
		end = jmp_spaces(line + start + node->hdoc + 1) - line;
    if (ft_strchr(line + end, ' '))
        end = ft_strchr(line + end, ' ') - line;
    else 
		end = ft_strlen(line);
	temp = ft_substr(line, start, end - start);
	if (search_out_quotes(temp, '>'))
		node->infile = ft_substr(temp, 0, search_out_quotes(temp, '>') - temp);
	else
		node->infile = ft_strdup(temp);
	free(temp);
	return (line_cutter(line, node->infile));
}

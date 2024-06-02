/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:14:11 by mikus             #+#    #+#             */
/*   Updated: 2024/06/02 21:23:30 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	resolve_infile(int *outpipe, int *inpipe, t_command *current)
{
	int		i;
	char	*file;

	i = 0;
	if (current->infile)
	{
		close(*inpipe);
		while (current->infile[i + 1])
			i++;
		if (current->infile[i]->special)
			*inpipe = manage_here_doc(current->infile[i]->name);
		else
		{
			file = current->infile[i]->name;
			*inpipe = open(file, O_RDONLY);
		}
	}
	else if (outpipe[0] > 0)
	{
		close(*inpipe);
		*inpipe = outpipe[0];
	}
}

void	resolve_outfile(int *outpipe, t_command *current)
{
	int		i;
	char	*file;

	i = 0;
	if (current->outfile)
	{
		while (current->outfile[i])
		{
			file = current->outfile[i]->name;
			if (current->outfile[i]->special)
				outpipe[1] = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
			else
				outpipe[1] = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			i++;
			if (current->outfile[i])
				close(outpipe[1]);
		}
	}
	else if (!current->next)
		outpipe[1] = dup(STDOUT_FILENO);
	else
		pipe(outpipe);
}

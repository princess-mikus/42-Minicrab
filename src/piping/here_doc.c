/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:12:28 by mikus             #+#    #+#             */
/*   Updated: 2024/05/23 23:12:33 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_here_doc(char *delimiter)
{
	char	*stream;
	int		pipefd[2];

	if (pipe(pipefd))
		return (-1);
	while (1)
	{
		stream = get_next_line(0);
		if (!ft_strncmp(stream, delimiter, ft_strlen(delimiter)))
			break ;
		else
			write(pipefd[1], stream, ft_strlen(stream));
		free(stream);
	}
	close (pipefd[1]);
	return (free(stream), pipefd[0]);
}

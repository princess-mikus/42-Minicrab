/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:12:28 by mikus             #+#    #+#             */
/*   Updated: 2024/06/08 16:28:34 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_here_doc(char **delimiter)
{
	char	*stream;
	int		i;
	int		pipefd[2];

	if (pipe(pipefd))
		return (-1);
	i = 0;
	while (1)
	{
		stream = get_next_line(0);
		if (!ft_strncmp(stream, delimiter[i], ft_strlen(delimiter[i])))
		{
			if (!delimiter[++i])
				break ;
		}
		else
			write(pipefd[1], stream, ft_strlen(stream));
		free(stream);
	}
	close (pipefd[1]);
	return (free(stream), pipefd[0]);
}

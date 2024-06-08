/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:37:15 by mikus             #+#    #+#             */
/*   Updated: 2024/06/08 13:17:07 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mx_error(const char *target)
{
	char	*error;

	error = ft_strjoin("minicrab: ", target);
	perror(error);
	free(error);
}

void	resolve_exec_error(int *inpipe, int *outpipe, char *program)
{
	struct stat	path_stat;

	stat(program, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		errno = EISDIR;
	else
		errno = ENOENT;
	mx_error(program);
	close(*inpipe);
	close(outpipe[1]);
}

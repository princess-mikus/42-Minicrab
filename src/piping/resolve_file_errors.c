/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_file_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:31:45 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/06/08 16:32:52 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_infile_error(char *file, bool *infile)
{
	struct stat	path_stat;

	stat(file, &path_stat);
	if (access(file, F_OK))
	{
		errno = ENOENT;
		mx_error(file);
		*infile = false;
		return (true);
	}
	if (!(path_stat.st_mode & S_IRUSR))
	{
		errno = EACCES;
		mx_error(file);
		*infile = false;
		return (true);
	}
	return (false);
}


bool	check_outfile_error(char *file, bool *outfile)
{
	struct stat	path_stat;

	stat(file, &path_stat);
	if (!access(file, F_OK) && !(path_stat.st_mode & S_IWUSR))
	{
		errno = EACCES;
		mx_error(file);
		*outfile = false;
		return (true);
	}
	return (false);
}
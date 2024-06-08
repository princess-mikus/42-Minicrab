/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:14:11 by mikus             #+#    #+#             */
/*   Updated: 2024/06/08 12:44:45 by fcasaubo         ###   ########.fr       */
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

void	resolve_infile(\
int *outpipe, int *inpipe, t_command *current, bool *infile)
{
	int			i;
	char		*file;
	bool		stop;

	i = -1;
	stop = false;
	if (!current->infile && outpipe[0] > 0)
	{
		close(*inpipe);
		*inpipe = outpipe[0];
	}
	while (current->infile && current->infile[++i] && !stop)
	{
			close(*inpipe);
			file = current->infile[i]->name;
		stop = check_infile_error(file, infile);
		if (current->infile[i]->special)
			*inpipe = manage_here_doc(file);
		else
			*inpipe = open(file, O_RDONLY);
	}
}

bool	check_outfile_error(char *file, bool *outfile)
{
	struct stat	path_stat;

	stat(file, &path_stat);
	if (!(path_stat.st_mode & S_IWUSR))
	{
		errno = EACCES;
		mx_error(file);
		*outfile = false;
		return (true);
	}
	return (false);
}

void	resolve_outfile(int *outpipe, t_command *current, bool *outfile)
{
	int			i;
	char		*file;
	bool		stop;

	i = 0;
	stop = false;
	while (!stop && current->outfile && current->outfile[i])
	{
		close(outpipe[1]);
		file = current->outfile[i]->name;
		stop = check_outfile_error(file, outfile);
		if (current->outfile[i]->special)
			outpipe[1] = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			outpipe[1] = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		i++;
	}
	if (!current->next)
		outpipe[1] = dup(STDOUT_FILENO);
	else
		pipe(outpipe);
}

bool	resolve_files(\
t_command *current, int *inpipe, int *outpipe, t_envp **envp_mx)
{
	bool	infile;
	bool	outfile;

	infile = true;
	outfile = true;
	resolve_infile(outpipe, inpipe, current, &infile);
	if (infile)
		resolve_outfile(outpipe, current, &outfile);
	if (!infile || !outfile)
	{
		add_var_to_envp_mx(envp_mx, "?", ft_itoa(errno));
		return (false);
	}
	return (true);
}

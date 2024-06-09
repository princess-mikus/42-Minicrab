/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:14:11 by mikus             #+#    #+#             */
/*   Updated: 2024/06/08 19:08:37 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		delimiter_len(t_file **infile)
{
	int i;
	int	len;

	i = 0;
	len = 1;
	if (infile && infile[i])
	{
		if (infile[i]->special)
			len++;
		i++;
	}
	return (len);
}

char	**resolve_here_doc(t_command *current)
{
	int		i;
	int		j;
	char	**delimiter;

	i = -1;
	j = 0;
	delimiter = ft_calloc(sizeof(char *), delimiter_len(current->infile));
	while (current->infile && current->infile[++i])
		if (current->infile[i]->special)
			delimiter[j++] = current->infile[i]->name;
	delimiter[j] = NULL;
	return (delimiter);
}

void	resolve_infile(\
int *outpipe, int *inpipe, t_command *current, bool *infile)
{
	int			i;
	char		*file;
	bool		stop;

	i = -1;
	stop = false;
	close(*inpipe);
	*inpipe = -1;
	if (!current->infile && outpipe[0] > 0)
	{
		close(*inpipe);
		*inpipe = outpipe[0];
	}
	while (current->infile && current->infile[++i] && !stop && !current->infile[i]->special)
	{
		close(*inpipe);
		file = current->infile[i]->name;
		stop = check_infile_error(file, infile);
		if (!stop)
			*inpipe = open(file, O_RDONLY);
	}
}

void	resolve_outfile(int *outpipe, t_command *current, bool *outfile)
{
	int			i;
	char		*file;
	bool		stop;

	i = 0;
	stop = false;
	if (!current->outfile)
	{
		if (!current->next)
			outpipe[1] = dup(STDOUT_FILENO);
		else
			pipe(outpipe);
	}
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
}

bool	resolve_files(\
t_command *current, int *inpipe, int *outpipe, t_envp **envp_mx)
{
	bool	infile;
	bool	outfile;
	char	**delimiter;

	infile = true;
	outfile = true;
	delimiter = resolve_here_doc(current);
	resolve_infile(outpipe, inpipe, current, &infile);
	if (infile)
		resolve_outfile(outpipe, current, &outfile);
	if (!infile || !outfile)
	{
		add_var_to_envp_mx(envp_mx, "?", ft_itoa(errno));
		return (free(delimiter), false);
	}
	if (delimiter[0])
		*inpipe = manage_here_doc(delimiter);
	free(delimiter);
	return (true);
}

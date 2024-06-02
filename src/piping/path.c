/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:16:46 by mikus             #+#    #+#             */
/*   Updated: 2024/06/02 13:37:38 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_var(char **envp)
{
	int		i;
	char	**splited;
	char	**to_return;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")))
		i++;
	if (!envp[i])
		return (NULL);
	splited = ft_split(envp[i], '=');
	to_return = ft_split(splited[1], ':');
	return (free_array((void **)splited), to_return);
}

char	*get_path(char	*program, char **path)
{
	char	*candidate;
	char	*appended;
	int		i;

	i = 0;
	appended = ft_strjoin("/", program);
	while (path && path[i])
	{
		candidate = ft_strjoin(path[i], appended);
		if (!access(candidate, F_OK))
			return (free_array((void **)path), free(appended), candidate);
		free(candidate);
		i++;
	}
	return (free_array((void **)path), free(appended), NULL);
}

void	check_local(t_command *current)
{
	char	**temp;
	int		i;

	if (!access(current->command, F_OK))
	{
		current->path = ft_strdup(current->command);
		temp = ft_split(current->command, '/');
		free(current->command);
		i = 0;
		while (temp[i + 1])
			i++;
		current->command = ft_strdup(temp[i]);
		free_array((void **)temp);
	}
	else
		current->path = NULL;
}

bool	resolve_path(t_command *current, char **path)
{
	current->path = NULL;
	check_local(current);
	if (!current->path)
		current->path = get_path(current->command, path);
	if (!current->path)
		return (false);
	return (true);
}

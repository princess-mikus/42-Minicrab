/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:36:07 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/04/15 15:34:03 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(void **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

char	*get_path(char	*program, char **path)
{
	char	*candidate;
	char	*program_2_la_venganza;
	int		i;

	i = -1;
	while (path[++i])
	{
		program_2_la_venganza = ft_strjoin("/", program);
		candidate = ft_strjoin(path[i], program_2_la_venganza);
		if (!access(candidate, F_OK))
			return (candidate);
	}
	return (NULL);
}

char	**get_path_var(t_envp *envp_mx)
{
	while (envp_mx && \
	ft_strncmp(envp_mx->variable, "PATH", ft_strlen(envp_mx->variable)))
		envp_mx = envp_mx->next;
	return (ft_split(envp_mx->content, ':'));
}

int	fork_and_execute(char *program, __unused int readpipe, char **envp, char **path_env)
{
	char	**arguments;
	char	*path;
	int		pipefd[2];

	arguments = ft_split(program, ' ');
	path = get_path(arguments[0], path_env);
	pipe(pipefd);
	if (!fork())
	{
		execve(path, arguments, envp);
		exit(2);
	}
	else
		wait(NULL);
	close(readpipe);
	close(pipefd[1]);
	return (free_array((void **)arguments), /*pipefd[0]*/0);
}

int		get_total_len(char **temp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (temp[++i])
		len += ft_strlen(temp[i]) + 1;
	return (len);
}

char	*get_infiles(char *command_line, int *pipe)
{
	int		i;
	int		j;
	char	**temp;
	char	*to_return;

	i = 0;
	while (command_line[i] == ' ')
		i++;
	if (command_line[i] == '<')
	{
		temp = ft_split(command_line + i + 1, ' ');
		to_return = ft_calloc(get_total_len(temp), sizeof(char));
		*pipe = open(temp[0], O_RDONLY);
		j = 0;
		while (temp[++j])
		{
			ft_strlcat(to_return, temp[j], ft_strlen(to_return));
			ft_strlcat(to_return, " ", ft_strlen(to_return));
		}
		return (free_array((void **)temp), to_return);
	}
	*pipe = dup(STDIN_FILENO);
	return (command_line);
}

void	print_results(int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (str)
	{
		write(1, str, ft_strlen(str));
		free(str);
		str = get_next_line(fd);
	}
}

int 	execute_commands(char **commands, t_envp *envp_mx)
{
	int 	i;
	int 	readpipe[2];
	char	**envp;
	char	**path;

	i = -1;
	envp = envp_mx_to_arg(&envp_mx);
	path = get_path_var(envp_mx);
	while (commands[++i])
	{
		commands[i] = get_infiles(commands[i], &readpipe[1]);
		if (!ft_strncmp(commands[i], "env", 4))
			env_mx(&envp_mx);
		else
			readpipe[1] = fork_and_execute(commands[i], readpipe[1], envp, path);
	}
	free_array((void **)path);
	free_array((void **)envp);
	return (0);
}

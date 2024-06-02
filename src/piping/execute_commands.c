/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:36:07 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/06/02 21:23:00 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_arguments(t_command *current)
{
	char	**to_return;
	int		i;

	i = 0;
	while (current->argv && current->argv[i])
		i++;
	to_return = malloc(sizeof(char *) * (i + 2));
	to_return[0] = ft_strdup(current->command);
	i = 0;
	while (current->argv && current->argv[i])
	{
		to_return[i + 1] = ft_strdup(current->argv[i]);
		i++;
	}
	to_return[i + 1] = NULL;
	return (to_return);
}

bool	has_permissions(char *program, char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (path_stat.st_mode & S_IXUSR)
		return (true);
	errno = EACCES;
	mx_error(program);
	return (false);
}

void	fork_and_execute( \
t_command *current, int *inpipe, int *outpipe, char **envp)
{
	char	**program;

	program = get_arguments(current);
	current->pid = fork();
	if (!current->pid)
	{
		if (!has_permissions(current->command, current->path))
			exit(EACCES);
		dup2(*inpipe, STDIN_FILENO);
		close(*inpipe);
		dup2(outpipe[1], STDOUT_FILENO);
		close(outpipe[1]);
		execve(current->path, program, envp);
		exit(2);
	}
	waitpid(current->pid, NULL, WNOHANG);
	close(*inpipe);
	close(outpipe[1]);
	free_array((void **)program);
}

void	select_execution(t_command *current, int inpipe, \
						int *outpipe, t_envp **envp_mx)
{
	char		**envp;

	envp = update_environment(current, envp_mx);
	if (get_builtin(current->command))
		execute_builtin(current, &inpipe, outpipe, envp_mx);
	else if (!resolve_path(current, get_path_var(envp)))
		resolve_exec_error(&inpipe, outpipe, current->command);
	else
		fork_and_execute(current, &inpipe, outpipe, envp);
	free_array((void **)envp);
}

int	execute_commands(t_command **commands, t_envp **envp_mx)
{
	int			outpipe[2];
	int			inpipe;
	t_command	*current;

	inpipe = dup(STDIN_FILENO);
	current = *commands;
	outpipe[0] = -1;
	outpipe[1] = -1;
	signal_sender(*commands);
	while (current)
	{
		resolve_infile(outpipe, &inpipe, current);
		resolve_outfile(outpipe, current);
		if (current->command)
			select_execution(current, inpipe, outpipe, envp_mx);
		if (current->next)
			current = current->next;
		else
			break ;
	}
	waitpid(current->pid, &current->status, 0);
	current->status = WEXITSTATUS(current->status);
	add_var_to_envp_mx(envp_mx, "?", ft_itoa(current->status));
	return (close(outpipe[0]), close(outpipe[1]), 0);
}

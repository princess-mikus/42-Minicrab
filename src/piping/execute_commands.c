/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:36:07 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/05/20 12:44:47 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_arguments(t_command *current)
{
	char	**temp;
	char	**to_return;
	int		i;

	i = 0;
	temp = ft_split(current->arg, ' ');
	while (temp && temp[i])
		i++;
	to_return = malloc(sizeof(char *) * (i + 2));
	to_return[0] = ft_strdup(current->command);
	i = 0;
	while (temp && temp[i])
	{
		to_return[i + 1] = ft_strdup(temp[i]);
		i++;
	}
	to_return[i + 1] = NULL;
	return (free_array((void **)temp), to_return);
}

void	fork_and_execute( \
t_command *current, int *inpipe, int *outpipe, char **envp)
{
	char	**program;

	program = get_arguments(current);
	current->pid = fork();
	if (!current->pid)
	{
		dup2(*inpipe, STDIN_FILENO);
		close(*inpipe);
		dup2(outpipe[1], STDOUT_FILENO);
		close(outpipe[1]);
		execve(current->path, program, envp);
		exit(2);
	}
	//waitpid(current->pid, &current->status, WNOHANG);
	waitpid(0, NULL, WNOHANG);
	close(*inpipe);
	close(outpipe[1]);
	free_array((void **)program);
}

void	resolve_infile(int *outpipe, int *inpipe, t_command *current)
{
	if (current->infile)
	{
		close(*inpipe);
		*inpipe = open(current->infile, O_RDONLY);
	}
	else if (outpipe[0] > 0)
	{
		close(*inpipe);
		*inpipe = outpipe[0];
	}
}

void	resolve_outfile(int *outpipe, t_command *current)
{
	if (current->outfile)
		outpipe[1] = open(current->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (!current->next)
		outpipe[1] = dup(STDOUT_FILENO);
	else
		pipe(outpipe);
}

int	execute_commands(t_command **commands, t_envp *envp_mx)
{
	int			outpipe[2];
	int			inpipe;
	t_command	*current;
	char		**envp;

	inpipe = dup(STDIN_FILENO);
	current = *commands;
	outpipe[0] = -1;
	outpipe[1] = -1;
	signal_sender(*commands);
	while (current)
	{
		resolve_infile(outpipe, &inpipe, current);
		resolve_outfile(outpipe, current);
		envp = update_environment(current, &envp_mx);
		if (get_builtin(current->command))
			execute_builtin(current, &inpipe, outpipe, &envp_mx);
		else if (!resolve_path(current, get_path_var(envp)))
			resolve_exec_error(&inpipe, outpipe);
		else
			fork_and_execute(current, &inpipe, outpipe, envp);
		free_array((void **)envp);
		if (current->next)
			current = current->next;
		else
			break;
	}
	waitpid(current->pid, &current->status, 0);
	current->status = WEXITSTATUS(current->status);
	//wait(&current->status);
	add_var_to_envp_mx(&envp_mx, "?", ft_itoa(current->status));
	return (close(outpipe[0]), close(outpipe[1]), 0);
}

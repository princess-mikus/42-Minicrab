/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:36:07 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/05/06 18:20:48 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char **get_arguments(t_command *current)
{
	char	**temp;
	char	**to_return;
	int		i;

	i = 0;
	temp = ft_split(current->arg, ' ');
	while (temp[i])
		i++;
	to_return = malloc(sizeof(char *) * (i + 2));
	to_return[0] = ft_strdup(current->command);
	i = 0;
	while (temp[i])
	{
		to_return[i + 1] = ft_strdup(temp[i]);
		i++;
	}
	to_return[i + 1] = NULL;
	return (free_array((void **)temp), to_return);
}

void	fork_and_execute(t_command *current, int *inpipe, int *outpipe, char **envp)
{
	char	**program;
	char	*path;

	program = get_arguments(current);
	path = get_path(current->command, get_path_var(envp));
	if (!fork())
	{
		dup2(*inpipe, STDIN_FILENO);
		close(*inpipe);
		dup2(outpipe[1], STDOUT_FILENO);
		close(outpipe[1]);
		execve(path, program, envp);
		exit(2);
	}
	else
		wait(NULL);
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
		outpipe[1] = open(current->outfile, O_CREAT, 0644);
	else if (!current->next)
		outpipe[1] = dup(STDOUT_FILENO);
	else
		pipe(outpipe);
}

int 	execute_commands(t_command **commands, t_envp *envp_mx)
{
	int 		outpipe[2];
	int			inpipe;
	t_command	*current;
	char		**envp;

	envp = envp_mx_to_arg(&envp_mx);
	inpipe = dup(STDIN_FILENO);
	current = *commands;
	outpipe[0] = -1;
	outpipe[1] = -1;
	while (current)
	{
		resolve_infile(outpipe, &inpipe, current);
		resolve_outfile(outpipe, current);
		ft_printf("Inpipe: %d, Outpipe: [0]: %d [1]: %d\n", inpipe, outpipe[0], outpipe[1]);
		fork_and_execute(current, &inpipe, outpipe, envp);

		current = current->next;
	}
	close(outpipe[0]);
	close(outpipe[1]);
	free_array((void **)envp);
	return (0);
}

/*
int main't(void)
{
			| < comando > |

Switch (linea):
	Infile:
		Si:  infile < comando | comando2
			close(infile[1])
			dup2(infile[1], open(archivo))
		No: comando | comando2
			Primer caso: comando
				inpipe[1] = dup(STDIN_FILENO);
			Demás casos: comandoN
				close(inpipe[0], inpipe[1]);
				dup2(inpipe[0], outpipe[1]);
	Outfile:
		Si: comando > outfile | comando2
			outpipe[0] = dup2(open(archivo);
		No: comando | comando2
			0 a n - 1 iteraciones: comandoX
				outpipefd[1] = ?
			Ultima: comandoN
				outpipefd[1] = dup(STDOUT_FILENO)
}
*/
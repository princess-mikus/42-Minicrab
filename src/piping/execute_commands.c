/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:36:07 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/04/23 16:04:33 by fcasaubo         ###   ########.fr       */
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
			return (free_array((void **)path), candidate);
	}
	return (free_array((void **)path), NULL);
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

void	fork_and_execute(char *program, int *inpipe, int *outpipe, char **envp)
{
	char	**arguments;
	char	*path;

	arguments = ft_split(program, ' ');
	path = get_path(arguments[0], get_path_var(envp));
	if (!fork())
	{
		dup2(*inpipe, STDIN_FILENO);
		close(*inpipe);
		dup2(outpipe[1], STDOUT_FILENO);
		close(outpipe[1]);
		execve(path, arguments, envp);
		exit(2);
	}
	else
		wait(NULL);
	close(*inpipe);
	close(outpipe[1]);
	free_array((void **)arguments);
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
	int 	outpipe[2];
	int		inpipe;
	char	**envp;

	i = 0;
	envp = envp_mx_to_arg(&envp_mx);
	inpipe = dup(STDIN_FILENO);
	while (commands[i])
	{
		if (commands[i + 1])
			pipe(outpipe);
		else
			outpipe[1] = dup(STDIN_FILENO);
		//commands[i] = get_infile(commands[i], &inpipe[1]);
		//commands[i] = get_outfile(commands[i], &outpipe[1]);
		fork_and_execute(commands[i], &inpipe, outpipe, envp);
		i++;
		inpipe = outpipe[0];
		printf("%d (%d) & %d\n", outpipe[0], inpipe, outpipe[1]);
	}
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
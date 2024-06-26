/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:08:02 by mikus             #+#    #+#             */
/*   Updated: 2024/06/08 13:20:28 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_builtin(char *program)
{
	if (\
		!ft_strncmp(program, "echo", ft_strlen("echo") + 1) || \
		!ft_strncmp(program, "cd", ft_strlen("cd") + 1) || \
		!ft_strncmp(program, "env", ft_strlen("env") + 1) || \
		!ft_strncmp(program, "export", ft_strlen("export") + 1) || \
		!ft_strncmp(program, "pwd", ft_strlen("pwd") + 1) || \
		!ft_strncmp(program, "unset", ft_strlen("unset") + 1))
		return (true);
	return (false);
}

int	choose_builtin(t_command *current, t_envp **envp_mx)
{
	if (!ft_strncmp(current->command, "echo", ft_strlen("echo") + 1))
		return (echo_mx(current->argv));
	if (!ft_strncmp(current->command, "env", ft_strlen("env") + 1))
		return (env_mx(envp_mx), 0);
	if (!ft_strncmp(current->command, "pwd", ft_strlen("pwd") + 1))
		return (pwd_mx());
	return (2);
}

bool	is_non_forked_builtin(t_command *current, t_envp **envp_mx)
{
	int	i;

	i = 0;
	if (!ft_strncmp(current->command, "cd", ft_strlen("cd") + 1))
	{
		current->status = cd_mx(envp_mx, current->argv);
		return (true);
	}
	if (!ft_strncmp(current->command, "export", ft_strlen("export") + 1))
	{
		export_mx(envp_mx, current->argv, current->dec);
		current->status = 0;
		return (true);
	}
	if (!ft_strncmp(current->command, "unset", ft_strlen("unset") + 1))
	{
		while (current->argv && current->argv[i])
			unset_mx(envp_mx, current->argv[i++]);
		current->status = 0;
		return (true);
	}
	return (false);
}

void	execute_builtin( \
t_command *current, int *inpipe, int *outpipe, t_envp **envp_mx)
{
	if (is_non_forked_builtin(current, envp_mx))
	{
		close(*inpipe);
		close(outpipe[1]);
		return ;
	}
	current->pid = fork();
	if (!current->pid)
	{
		dup2(*inpipe, STDIN_FILENO);
		close(*inpipe);
		dup2(outpipe[1], STDOUT_FILENO);
		close(outpipe[1]);
		current->status = choose_builtin(current, envp_mx);
		exit(current->status);
	}
	waitpid(current->pid, NULL, WNOHANG);
	close(*inpipe);
	close(outpipe[1]);
}

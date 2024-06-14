/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:36:45 by mikus             #+#    #+#             */
/*   Updated: 2024/06/07 12:28:01 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_sig;

void	get_signal(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_management(void)
{
	signal(SIGINT, get_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	kill_yourself(int sig)
{
	(void)sig;
	exit(130);
}

void	kill_children(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		write(1, "\n", 1);
	g_sig = sig;
}

void	signal_sender(t_command *command)
{
	signal(SIGINT, kill_children);
	signal(SIGQUIT, kill_children);
	if (g_sig == SIGQUIT)
	{
		while (command)
		{
			kill(command->pid, SIGQUIT);
			command = command->next;
		}
	}
	if (g_sig == SIGINT)
	{
		while (command)
		{
			kill(command->pid, SIGINT);
			command = command->next;
		}
	}
}

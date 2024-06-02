/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:36:45 by mikus             #+#    #+#             */
/*   Updated: 2024/06/02 21:25:14 by mikus            ###   ########.fr       */
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

void	kill_children(int sig)
{
	g_sig = sig;
}

void	signal_sender(t_command *command)
{
	signal(SIGQUIT, kill_children);
	if (g_sig == SIGQUIT)
	{
		while (command)
		{
			kill(command->pid, SIGQUIT);
			command = command->next;
		}
	}
}

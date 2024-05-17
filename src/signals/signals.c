/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:36:45 by mikus             #+#    #+#             */
/*   Updated: 2024/05/17 01:16:11 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	stop_signal(int sig)
{	
	if (sig == SIGINT)
	{
    	write(2, "\n", 1);
    	rl_replace_line("", 0);
    	rl_on_new_line();
    	rl_redisplay();
	}
}
	
void    signal_management(void)
{
	signal(SIGINT, stop_signal);
}

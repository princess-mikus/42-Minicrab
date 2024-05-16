/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:37:15 by mikus             #+#    #+#             */
/*   Updated: 2024/05/16 21:02:21 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mx_error(int error_number)
{
	if (error_number > 0)
		printf("TEMPORAL: Working on implementing errors xd\n");
}

void	resolve_exec_error(int *inpipe, int *outpipe)
{
	close(*inpipe);
	close(outpipe[1]);
	mx_error(ENOENT);
}

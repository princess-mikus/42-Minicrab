/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:37:15 by mikus             #+#    #+#             */
/*   Updated: 2024/05/29 10:17:21 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mx_error(const char *target)
{
	char	*error;

	error = ft_strjoin("minicrab: ", target);
	perror(error);
	free(error);
}

void	resolve_exec_error(int *inpipe, int *outpipe, char *program)
{
	close(*inpipe);
	close(outpipe[1]);
	mx_error(program);
}

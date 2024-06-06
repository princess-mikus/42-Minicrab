/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:18:55 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/06/03 10:43:41 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    return_status(int status, t_command *current)
{
    current->pid = fork();
    if (!current->pid)
        exit (status);
    waitpid(0, NULL, WNOHANG);
}

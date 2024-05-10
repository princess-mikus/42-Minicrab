/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:57:30 by mikus             #+#    #+#             */
/*   Updated: 2024/05/10 15:28:03 by mikus            ###   ########.fr       */
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

void	free_command_list(t_command **list)
{
	t_command	*next;
	t_command	*current;

	current = *list;
	while (current)
	{
		next = current->next;
		free(current->infile);
		free(current->command);
		free(current->arg);
		free(current->outfile);
		free(current);
		current = next;
	}
	list = NULL;
}
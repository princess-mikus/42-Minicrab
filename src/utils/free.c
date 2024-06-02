/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:57:30 by mikus             #+#    #+#             */
/*   Updated: 2024/05/27 13:47:52 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(void **array)
{
	int	i;

	i = -1;
	while (array && array[++i])
		free(array[i]);
	free(array);
}

void	free_files(t_command *current)
{
	int	i;

	i = 0;
	while (current->dec[i])
	{
		if (current->dec[i]->name)
			free(current->dec[i]->name);
		free(current->dec[i]);
	}
	while (current->infile[i])
	{
		if (current->infile[i]->name)
			free(current->infile[i]->name);
		free(current->infile[i]);
	}
	while (current->outfile[i])
	{
		if (current->outfile[i]->name)
			free(current->outfile[i]->name);
		free(current->outfile[i]);
	}
}

void	free_command_list(t_command **list)
{
	t_command	*next;
	t_command	*current;

	current = *list;
	while (current)
	{
		next = current->next;
		free(current->command);
		//free_array((void **)current->arg);
		//free_files(current);
		free(current);
		current = next;
	}
	list = NULL;
}

void	free_envp_mx(t_envp **envp_mx)
{
	t_envp	*current;
	t_envp	*next;

	if (!envp_mx || !*envp_mx)
		return ;
	current = *envp_mx;
	while (current)
	{
		next = current->next;
		if (current->variable[0] != '~')
		{
			free(current->variable);
			free(current->content);
		}
		free(current);
		current = next;
	}
}

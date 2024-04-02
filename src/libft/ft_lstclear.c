/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:45:32 by xortega           #+#    #+#             */
/*   Updated: 2024/01/24 14:24:01 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current_node;
	t_list	*next;

	if (*lst && del)
	{
		current_node = *lst;
		while (current_node)
		{
			next = current_node -> next;
			if (current_node -> content && del)
				del(current_node -> content);
			free(current_node);
			current_node = next;
		}
	}
	*lst = NULL;
}

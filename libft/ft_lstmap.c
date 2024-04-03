/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:49:35 by xortega           #+#    #+#             */
/*   Updated: 2024/04/03 12:44:02 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current_node;
	t_list	*current_new_node;
	t_list	*newlist;
	void	*content;

	newlist = NULL;
	if (lst && f && del)
	{
		current_node = lst;
		while (current_node)
		{
			content = f(current_node -> content);
			current_new_node = ft_lstnew(content);
			if (!current_new_node)
			{
				free(content);
				ft_lstclear(&newlist, del);
				return (NULL);
			}
			ft_lstadd_back (&newlist, current_new_node);
			current_node = current_node -> next;
		}
	}
	return (newlist);
}

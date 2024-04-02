/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:33:57 by xortega           #+#    #+#             */
/*   Updated: 2024/01/24 14:24:01 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count == 2147483647 || size == 2147483647)
		return (NULL);
	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	if (count == 0)
		return (str);
	return (ft_memset(str, '\0', (count * size)));
}

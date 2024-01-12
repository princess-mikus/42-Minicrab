/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:49:36 by xortega           #+#    #+#             */
/*   Updated: 2024/01/12 14:40:52 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_check(char c, va_list lst)
{
	if (c == 'c')
		return (print_char(lst));
	else if (c == 's')
		return (print_string(lst));
	else if (c == 'p')
		return (print_addres(lst));
	else if (c == 'd' || c == 'i')
		return (print_number(lst));
	else if (c == 'u')
		return (print_unsigned(lst));
	else if (c == 'x' || c == 'X')
		return (print_hex(lst, c));
	else if (c == '%')
		return ((int)write(1, "%", 1));
	return (0);
}

int	ft_printf(char const *str, ...)
{
	va_list	lst;
	int		out;
	int		counter;
	int		write_count;

	counter = 0;
	out = 0;
	va_start(lst, str);
	while (str[counter])
	{
		if (str[counter] == '%')
		{
			write_count = ft_check(str[++counter], lst);
			if (write_count == -1)
				return (write_count);
			out += write_count;
		}
		else
			out += (write(1, &str[counter], 1));
		counter++;
	}
	va_end(lst);
	return (out);
}

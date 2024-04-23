/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:11:09 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/04/23 16:06:43 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

typedef struct s_envp
{
	char			*variable;
	char			*content;
	bool			exported;
	struct s_envp	*next;	
}				t_envp;

typedef struct s_input
{
	char		*line;
	char		*line_exp;
	char		**line_sp;
	char		**command;
}					t_input;

typedef struct s_data
{
	char			**envp;
	char			**envp_mx;
	t_input			*input;
}					t_data;

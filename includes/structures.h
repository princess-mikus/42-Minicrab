/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:11:09 by fcasaubo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/23 22:20:33 by mikus            ###   ########.fr       */
=======
/*   Updated: 2024/05/17 14:06:17 by mikus            ###   ########.fr       */
>>>>>>> parent of 6c6710e (Merging parsing into built-ins)
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

typedef struct s_envp
{
	char			*variable;
	char			*content;
	bool			exported;
	struct s_envp	*next;	
}					t_envp;

typedef struct s_command
{
	t_file				**dec;
	t_file				**infile;
	t_file				**outfile;
	char				*command;
	char				*arg;
	char				*path;
	char				*outfile;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char			**envp;
	char			**envp_mx;
}					t_data;

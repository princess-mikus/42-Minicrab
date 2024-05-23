/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:11:09 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/05/17 14:06:17 by mikus            ###   ########.fr       *
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

typedef struct s_file
{
	char	*name;
	bool	special;
}			t_file;

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
	pid_t				pid;
	int					status;
	char				*command;
	char				*arg;
	char				*path;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char			**envp;
	char			**envp_mx;
}					t_data;

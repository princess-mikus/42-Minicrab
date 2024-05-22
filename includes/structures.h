/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:11:09 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/05/22 14:51:45 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

typedef struct s_file
{
	int		class;
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
	bool				hdoc;
	bool				apend;
	char				**dec; //0
	char				**infile; //1
	char				**outfile; //2
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

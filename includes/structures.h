/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:11:09 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/06/08 17:04:33 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

//The envp is stored in the s_envp struct, a null terminated linked list
typedef struct s_envp
{
//contains the name of the variable, "PWD" for example
	char			*variable;
//contains the content of that variable, "/home/user" for example
	char			*content;
//a boolean flag marking if it has been exported  (1 || 0)
	bool			exported;
//a pointer to the next node if exist, the last node points to NULL
	struct s_envp	*next;	
}					t_envp;

typedef struct s_file
{
	char	*name;
	bool	special;
}			t_file;

typedef struct s_command
{
	t_file				**dec;
	t_file				**infile;
	t_file				**outfile;
	pid_t				pid;
	int					status;
	char				*command;
	char				*arg;
	char				**argv;
	char				*path;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char			**envp;
	char			**envp_mx;
}					t_data;

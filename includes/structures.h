/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:11:09 by fcasaubo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/17 14:06:17 by mikus            ###   ########.fr       */
=======
/*   Updated: 2024/05/17 11:50:53 by codespace        ###   ########.fr       */
>>>>>>> cleaning
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
	bool				hdoc;
	bool				apend;
	pid_t				pid;
	int					status;
	char				**dec;
	char				*infile;
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

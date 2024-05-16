/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:11:09 by fcasaubo          #+#    #+#             */
/*   Updated: 2024/05/16 12:23:51 by mikus            ###   ########.fr       */
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

typedef	struct s_command
{
	bool				hdoc;
	bool				apend;
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

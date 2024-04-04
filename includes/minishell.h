/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:24:31 by xortega           #+#    #+#             */
/*   Updated: 2024/04/04 15:44:33 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>
//#include "../libs/readline/readline.h"
//#include "readline.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_envp
{
	char			*variable;
	char			*content;
	struct s_envp	*next;	
}				t_envp;

typedef struct s_input
{
	char		*imput;
	char		**line_sp;
	char		**command;
}					t_input;

typedef struct s_data
{
	char			**envp;
	char			**envp_mx;
	t_input			*input;
}					t_data;

//ENV
void	init_envp(t_envp **envp_mx, char **envp);
void	envp_add(t_envp **envp_mx, t_envp *new);
void	envp_erase(t_envp **envp_mx, char *variable);
t_envp	*new_envp(char *variable, char *content);
#endif

//cargate el old_pwd;
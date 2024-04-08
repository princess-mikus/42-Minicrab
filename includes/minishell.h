/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:24:31 by xortega           #+#    #+#             */
/*   Updated: 2024/04/08 14:32:53 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>
//#include "../libs/readline/readline.h"
//#include "readline.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_envp
{
	char			*variable;
	char			*content;
	bool			exported;
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
//recibes a null terminated &t_envp and the envp, inicialite the envp_mx list whit the shell variables - OLDPWD
void	init_envp(t_envp **envp_mx, char **envp);
//given a pointer to the envp_mx list and a new node adds it to the end of the list
void	envp_add(t_envp **envp_mx, t_envp *new);
//create a t_envp node whit the variable and content and returns it
t_envp	*new_envp(char *variable, char *content);
//given a pointer to the list and a variable name checks if the variable is in the envp_mx return (1) if it is (0) if not
int		is_envp(t_envp **envp_mx, char *variable);
//given a pointer to the list and a variable name returns its content if exits
char	*get_content_envp_mx(t_envp **envp_mx, char *variable);
//BUILT-IN
//given a pointer to the list and a variable name it erase it from the list (keeping the list the same whiout the erased node)
void	unset_mx(t_envp **envp_mx, char *variable);
//built-in env prints the env
void	env_mx(t_envp **envp_mx);
//given a pointer to the list and a variable name change the bolean of exported  to true
void	export_mx(t_envp **envp_mx, char *variable);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:24:31 by xortega           #+#    #+#             */
/*   Updated: 2024/05/06 14:06:37 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "structures.h"
#include <stdio.h>
#include <stdbool.h>
#include <wait.h>
//#include "../libs/readline/readline.h"
//#include "readline.h"
#include <readline/readline.h>
#include <readline/history.h>

//ENV
//given a pointer to the list, a variable name and its content add its to the back of the list. if the list dosent exist inizialize it
void	add_var_to_envp_mx(t_envp **envp_mx, char *variable, char *content);
//recibes a null terminated &t_envp and the envp, inicialite the envp_mx list whit the shell variables - OLDPWD
void	init_envp(t_envp **envp_mx, char **envp);
//given a pointer to the envp_mx list and a new node adds it to the end of the list
void	envp_add_back(t_envp **envp_mx, t_envp *new);
//create a t_envp node whit the variable and content and returns it
t_envp	*new_envp(char *variable, char *content);
//given a pointer to the list and a variable name checks if the variable is in the envp_mx return (1) if it is (0) if not
int		is_envp(t_envp **envp_mx, char *variable);
//given a pointer to the list and a variable name returns its content if exits
char	*get_content_envp_mx(t_envp **envp_mx, char *variable);
//free the envp_mx
void	free_envp_mx(t_envp **envp_mx);
// A
char	**envp_mx_to_arg(t_envp **envp_mx);
// B
t_envp	*get_node_envp_mx(t_envp **envp_mx, char *variable);
//BUILT-IN
//given a pointer to the list and a variable name it erase it from the list (keeping the list the same whiout the erased node)
void	unset_mx(t_envp **envp_mx, char *variable);
//built-in env prints the env
void	env_mx(t_envp **envp_mx);
//given a pointer to the list and a variable name change the bolean of exported  to true
void	export_mx(t_envp **envp_mx, char *variable);
// PARSING
// Parse and add to command list
void    parse(char *line_expanded, t_command **commands);
//EXPAND
char	*expansion(t_envp **envp_mx, char *imput);
/* PIPING (NOT FINAL) */
// Parse commands by ; then by |
void	parse_commands(char *line, t_envp *envp_mx);

// Pipex pero mejorao
int 	execute_commands(t_command **commands, t_envp *envp_mx);

//UTILS
void	free_array(void **array);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:05:30 by mikus             #+#    #+#             */
/*   Updated: 2024/05/22 15:24:33 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structures.h"
# include <stdio.h>
# include <stdbool.h>
# include <wait.h>
# include <signal.h>
# include <errno.h>
//#include "../libs/readline/readline.h"
//#include "readline.h"
# include <readline/readline.h>
# include <readline/history.h>

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
// Prints current working directory
int		pwd_mx(void);
// Changes current working directory
int		cd_mx(t_envp **envp_mx, char *args);
// Prints whatever trash you pass him
int		echo_mx(char *arguments);
// PARSING
// Parse and add to command list
void	parse(char *line_expanded, t_command **commands);
	//listing
void	init_node(t_command *node, char *line);
t_command	*new_command(char *line);
void	add_command(char *line_splited, t_command **commands);
	//tokenicing
char	*get_infile(char *line, char **infile);
char	*get_outfile(char *line, char **outfile);
int	start_dec(char *line);
char	*get_dec(char *line, t_command *node);
char	*get_cmd(char *line, t_command *node);
void	get_arg(char *line, t_command *node);
    //cleaning
void	cleaning(t_command *node);
//EXPAND
char	*expansion(t_envp **envp_mx, char *input);
// PIPING
// Calls parse and then passes command for execution
void	parse_commands(char *line, t_envp *envp_mx);

// Executes commands, either local files marked as executable, builtins or PATH programs
int		execute_commands(t_command **commands, t_envp *envp_mx);

// Updates envp before execution, with optional same-line vars
char	**update_environment(t_command *current, t_envp **envp_mx);

// Puts optional same-line vars to temp envp_mx
void	dec_to_env(char **dec, t_envp **envp_mx_temp);

// Executes mx_ built-ins
void	execute_builtin(t_command *current, int *inpipe, int *outpipe, t_envp **envp_mx);

// Checks if input is subject-mandated mx_ built-in
bool	get_builtin(char *program);

// Takes PATH var and splits it into a double pointer with every PATH path
char	**get_path_var(char **envp);

// Checks if file exists on PATH or if is a local file (Relative & Absolute paths)
bool	resolve_path(t_command *current, char **path);

// SIGNALS
void    signal_management(void);
void	signal_sender(t_command *command);

//UTILS
	//free
void	free_array(void **array);
void	free_command_list(t_command **list);
	//error-handeling
void	mx_error(int error_number);
void	resolve_exec_error(int *inpipe, int *outpipe);
	//strings
char	*jmp_spaces(char *str);
int	count_out_quotes(char *line, char c);
int	c_out_q_no_d(char *line, char c);
char	*search_out_quotes(char *line, char c);
char	*search_out_quotes(char *line, char c);
char	*line_cutter(char *line, char *to_cut);
#endif

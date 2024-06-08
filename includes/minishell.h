/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xortega <xortega@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:05:30 by mikus             #+#    #+#             */
/*   Updated: 2024/06/08 13:19:32 by xortega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structures.h"
# include <stdio.h>
# include <stdbool.h>
# include <wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
//#include "../libs/readline/readline.h"
//#include "readline.h"
# include <readline/readline.h>
# include <readline/history.h>

//	ENV
//see the struct s_envp in the structures.h file

// Given a pointer to the list, a variable name and its content
//add its to the back of the list. if the list dosent exist inizialize it
void		add_var_to_envp_mx(t_envp **envp_mx, char *variable, char *content);

// Recibes a null terminated &t_envp and the envp,
//inicialite the envp_mx list whit the shell variables - OLDPWD
void		init_envp(t_envp **envp_mx, char **envp);

// Given a pointer to the envp_mx list and a new node
//adds it to the end of the list
void		envp_add_back(t_envp **envp_mx, t_envp *new);

// Given a variable name and a content
//create a t_envp node whit the variable and content and returns it
t_envp		*new_envp(char *variable, char *content);

// Given a pointer to the list and a variable name
//checks if the variable is in the envp_mx return (1) if it is (0) if not
int			is_envp(t_envp **envp_mx, char *variable);

// Given a pointer to the list and a variable name
//returns its content if exits
char		*get_content_envp_mx(t_envp **envp_mx, char *variable);

// Given a pointer to the list
//free the envp_mx
void		free_envp_mx(t_envp **envp_mx);

// Given a pointer to the list
//create a char** whit every exported node whit the format(name=content)
char		**envp_mx_to_arg(t_envp **envp_mx);

// Given a pointer to the list and the name of a variable
//returns the node whit that name (returns null if it does not exit)
t_envp		*get_node_envp_mx(t_envp **envp_mx, char *variable);

//	BUILT-IN
//there are 7 buit-ins (cd, echo, env, export, pwd, unset, exit) 

// Given a pointer to the enpv list and a variable name
//it erase it from the list (keeping the list the same whiout the erased node)
void		unset_mx(t_envp **envp_mx, char *variable);

// Given a pointer to the envp list
//prints the env
void		env_mx(t_envp **envp_mx);

// Given a pointer to the envp list and a variable name
//change the bolean of exported to true
void		export_mx(t_envp **envp_mx, char *variable);

// Prints current working directory
int			pwd_mx(void);

// Given a pointer to the envp list and the arguments
//changes current working directory
int			cd_mx(t_envp **envp_mx, char **args);

// Given the arguments
//prints whatever trash you pass him
int			echo_mx(char **arguments);

//	PARSING
//the parsing is done in the next order:
//	user promt -> expand the variables -> divide in tokens -> clear the tokens

//	EXPAND
//it will create a char* coping the promt but
//with the content of the variable in the place of the variable name
//the expansion searchs for 2 flags '$' or '~'
//it never expans if the flags are betwen non scaped single quotes
//'$' expands betwen non scaped bouble cuotes, '~' dont
//the variable name is everything betwen the '$' and the first space after it

// Given a pointer to the envp list and the user promt
//create a char * with the expanded line
char		*expansion(t_envp **envp_mx, char *input);

// Given the expanded line and a pinter to the commands list
//will divide the line by the caracter '|'
//and send to add_command each divided line 
void		parse(char *line_expanded, t_command **commands);

//	COMMAND LIST
//from now on the tokens whill be stored in the struct s_command linked list

// Given the splited line and a pointer to the first node
//create a node calling new_comand and appends it to the end of the list 
void		add_command(char *line_splited, t_command **commands);

// Given the splited line
//reserves memory for a node, calls init_node and returns it
t_command	*new_command(char *line);

// Given a pointer to the node and the splited line
//inicialices the node
void		init_node(t_command *node, char *line);

//tokenicing
char		*get_infile(char *line, char **infile);
char		*get_outfile(char *line, char **outfile);
int			start_dec(char *line);
char		*get_dec(char *line, t_command *node);
char		*get_cmd(char *line, t_command *node);
void		get_arg(char *line, t_command *node);
//cleaning
void		cleaning(t_command *node);
int			quote_case(char *line);
char		*make_line(char *str);
//INTEGRITY
bool		check_integrity(char *line);
// PIPING
// Calls parse and then passes command for execution
void		parse_commands(char *line, t_envp **envp_mx);

// Executes commands,
//either local files marked as executable, builtins or PATH programs
int			execute_commands(t_command **commands, t_envp **envp_mx);

void		resolve_infile(int *outpipe, int *inpipe, t_command *current);
void		resolve_outfile(int *outpipe, t_command *current);

// Reads fd 0 when <<
int			manage_here_doc(char *delimiter);

// Updates envp before execution, with optional same-line vars
char		**update_environment(t_command *current, t_envp **envp_mx);

// Puts optional same-line vars to temp envp_mx
void		dec_to_env(t_file **dec, t_envp **envp_mx_temp);

// Executes mx_ built-ins
void		execute_builtin(\
	t_command *current, int *inpipe, int *outpipe, t_envp **envp_mx);

// Checks if input is subject-mandated mx_ built-in
bool		get_builtin(char *program);

// Takes PATH var and splits it into a double pointer with every PATH path
char		**get_path_var(char **envp);

// Checks if file exists on PATH or if is a local file
//(Relative & Absolute paths)
bool		resolve_path(t_command *current, char **path);

// SIGNALS
void		signal_management(void);
void		signal_sender(t_command *command);

//UTILS
void		free_array(void **array);
void		free_command_list(t_command **list);
void		mx_error(char const *target);
void		resolve_exec_error(int *inpipe, int *outpipe, char *program);
int			quote_case(char *line);
	//strings
char		*jmp_spaces(char *str);
int			count_out_quotes(char *line, char c);
int			c_out_q_no_d(char *line, char c);
char		*search_out_quotes(char *line, char c);
char		*search_out_quotes(char *line, char c);
char		*line_cutter(char *line, char *to_cut);
#endif

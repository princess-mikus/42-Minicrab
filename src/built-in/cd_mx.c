/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:47:20 by xortega           #+#    #+#             */
/*   Updated: 2024/05/17 00:23:41 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	home_case(t_envp **envp_mx)
{
	char	*home;

	home = get_content_envp_mx(envp_mx, "HOME");
	if (!home)
		return (ft_putstr_fd("minicrab: cd: HOME not set\n", 2), 2);
	add_var_to_envp_mx(envp_mx, "OLDPWD", \
	get_node_envp_mx(envp_mx, "PWD")->content);
	get_node_envp_mx(envp_mx, "PWD")->content = home;
	chdir(home);
	return (0);
}

int	dash_case(t_envp **envp_mx)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = get_content_envp_mx(envp_mx, "OLDPWD");
	if (!old_pwd)
		return (ft_putstr_fd("minicrab: cd: OLDPWD not set\n", 2), 2);
	pwd = get_content_envp_mx(envp_mx, "PWD");
	get_node_envp_mx(envp_mx, "OLDPWD")->content = pwd;
	get_node_envp_mx(envp_mx, "PWD")->content = old_pwd;
	chdir(old_pwd);
	return (0);
}

int	normal_case(t_envp **envp_mx, char *args)
{
	if (access(args, F_OK))
		return (perror("minicrab: cd"), ENOENT);
	add_var_to_envp_mx(envp_mx, "OLDPWD", \
	get_node_envp_mx(envp_mx, "PWD")->content);
	get_node_envp_mx(envp_mx, "PWD")->content = ft_strdup(args);
	chdir(args);
	return (0);
}

int	cd_mx(t_envp **envp_mx, char *args)
{
	if (!args)
		home_case(envp_mx);
	else if (args[0] == '-' && args[1] == '\0')
		dash_case(envp_mx);
	else
		normal_case(envp_mx, args);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:47:20 by xortega           #+#    #+#             */
/*   Updated: 2024/05/16 20:52:54 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	home_case(t_envp **envp_mx)
{
	char	*home;

	home = get_content_envp_mx(envp_mx, "HOME");
	if (!home)
		return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 2);
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
		return (ft_putstr_fd("bash: cd: OLDPWD not set\n", 2), 2);
	pwd = get_content_envp_mx(envp_mx, "PWD");
	get_node_envp_mx(envp_mx, "OLDPWD")->content = pwd;
	get_node_envp_mx(envp_mx, "PWD")->content = old_pwd;
	chdir(old_pwd);
	return (0);
}

int	cd_mx(t_envp **envp_mx, char *args)
{
	if (!args)
		return (home_case(envp_mx));
	if (args[0] == '-' && args[1] == '\0')
		return (dash_case(envp_mx));
	chdir(args);
	return (0);
}

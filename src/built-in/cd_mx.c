/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:47:20 by xortega           #+#    #+#             */
/*   Updated: 2024/06/06 12:55:54 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	home_case(t_envp **envp_mx)
{
	char	*home;

	home = get_content_envp_mx(envp_mx, "HOME");
	if (!home)
		return (ft_putstr_fd("minicrab: cd: HOME not set\n", 2), 1);
	add_var_to_envp_mx(envp_mx, ft_strdup("OLDPWD"), \
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
		return (ft_putstr_fd("minicrab: cd: OLDPWD not set\n", 2), 1);
	pwd = get_content_envp_mx(envp_mx, "PWD");
	get_node_envp_mx(envp_mx, "OLDPWD")->content = pwd;
	get_node_envp_mx(envp_mx, "PWD")->content = old_pwd;
	chdir(old_pwd);
	return (0);
}

static int	normal_case(t_envp **envp_mx, char *args)
{
	struct stat	path_stat;

	if (access(args, F_OK))
		return (mx_error("cd"), ENOENT);
	stat(args, &path_stat);
	if (!S_ISDIR(path_stat.st_mode))
	{
		errno = ENOTDIR;
		return (mx_error("cd"), ENOTDIR);
	}
	add_var_to_envp_mx(envp_mx, ft_strdup("OLDPWD"), \
	ft_strdup(get_node_envp_mx(envp_mx, "PWD")->content));
	get_node_envp_mx(envp_mx, "PWD")->content = getcwd(NULL, 0);
	chdir(args);
	return (0);
}

int	cd_mx(t_envp **envp_mx, char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	if (i > 1)
	{
		errno = E2BIG;
		return (mx_error("cd"), E2BIG);
	}
	if (!args || !args[0])
		return (home_case(envp_mx));
	else if (args[0][0] == '-' && args[0][1] == '\0')
		return (dash_case(envp_mx));
	else
		return (normal_case(envp_mx, args[0]));
}

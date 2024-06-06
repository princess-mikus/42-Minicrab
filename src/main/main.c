/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:50 by xortega           #+#    #+#             */
/*   Updated: 2024/06/06 21:25:10 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_rl_prompt(void)
{
	const char	*text = "🦀\e[0;93mminicrab: \e[0;97m";
	char		buff[4096];
	char		*ret;
	char		*temp;

	temp = ft_strjoin(text, getcwd(buff, 4096));
	ret = ft_strjoin(temp, " > \e[0;37m");
	free(temp);
	return (ret);
}

void	execute(char *line, t_envp **envp_mx)
{
	if (line[0] && line[0] != '\n')
	{
		add_history(line);
		parse_commands(line, envp_mx);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envp		*envp_mx;
	char		*line;
	int			status;
	char		*prompt;

	if (argc == 0 || !argv[0] || !envp)
		return (0);
	envp_mx = NULL;
	init_envp(&envp_mx, envp);
	while (1)
	{
		signal_management();
		prompt = get_rl_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line || !ft_strncmp(line, "exit", 5))
			break ;
		execute(line, &envp_mx);
		free(line);
	}
	ft_printf("exit\n");
	status = ft_atoi(get_content_envp_mx(&envp_mx, "?"));
	free_envp_mx(&envp_mx);
	clear_history();
	return (status);
}

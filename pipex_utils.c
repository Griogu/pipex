/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpendilh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:44:43 by mpendilh          #+#    #+#             */
/*   Updated: 2024/12/10 15:11:29 by mpendilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	error_management(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit(0);
}

char	*get_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*get_cmd(char **all_path, char **all_cmd)
{
	int		i;
	char	*tmp;
	char	*test_exec;
	char	*cmd;

	cmd = all_cmd[0];
	i = 0;
	if (!cmd || !cmd[0] || !access(cmd, F_OK | X_OK))
	{
		if (cmd && cmd[0])
			all_cmd[0] = NULL;
		return (cmd);
	}
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], "/");
		test_exec = ft_strjoin(tmp, cmd);
		free(tmp);
		if (test_exec && !access(test_exec, F_OK | X_OK))
			return (test_exec);
		free(test_exec);
		i++;
	}
	return (NULL);
}

void	pipex(t_vars *vars, char **envp)
{
	vars->path = get_path(envp);
	if (!vars->path)
		close_files(vars, "ERROR : PATH no found.\n");
	vars->all_path = ft_split(vars->path, ':');
	if (!vars->all_path)
		close_files(vars, "ERROR : Split failed.\n");
	vars->cmd1 = get_cmd(vars->all_path, vars->all_cmd1);
	vars->cmd2 = get_cmd(vars->all_path, vars->all_cmd2);
	free_tab(vars->all_path);
	if (!vars->cmd2)
	{
		if (!vars->cmd1)
		{
			free_all(vars);
			close_files(vars, "pipex : Command not found.\n");
		}
	}
	process(vars, envp);
}

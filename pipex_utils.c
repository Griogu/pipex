/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpendilh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:44:43 by mpendilh          #+#    #+#             */
/*   Updated: 2024/11/17 11:09:50 by mpendilh         ###   ########.fr       */
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
	int		j;
	char	*res;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		res = ft_substr(envp[i], 0, ft_strlen(envp[i]));
		if (!ft_strncmp(res, "PATH", 4))
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

static char	*get_cmd(char **all_cmd, char *cmd)
{
	int		i;
	char	*tmp;
	char	*test_exec;

	i = 0;
	while (all_cmd[i])
	{
		tmp = ft_strjoin(all_cmd[i], "/");
		test_exec = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(test_exec, F_OK | X_OK))
			return (test_exec);
		i++;
	}
	return (NULL);
}

void	pipex(t_vars *vars, char **envp)
{
	vars->path = get_path(envp);
	if (!vars->path || !vars->path[0])
		close_files(vars, "ERROR : PATH no found.\n");
	vars->all_path = ft_split(vars->path, ':');
	free(vars->path);
	if (!vars->all_path || !vars->all_path[0])
		close_files(vars, "ERROR : Split failed.\n");
	vars->cmd1 = get_cmd(vars->all_path, vars->all_cmd1[0]);
	if (!vars->cmd1)
	{
		free_tab(vars->all_path);
		close_files(vars, "pipex : Command not found.\n");
	}
	vars->cmd2 = get_cmd(vars->all_path, vars->all_cmd2[0]);
	free_tab(vars->all_path);
	if (!vars->cmd2)
	{
		free(vars->cmd1);
		close_files(vars, "pipex : Command not found.\n");
	}
	process(vars, envp);
}

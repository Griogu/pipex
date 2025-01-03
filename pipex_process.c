/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpendilh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:15:29 by mpendilh          #+#    #+#             */
/*   Updated: 2024/11/29 11:48:59 by mpendilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static void	ft_execve(char *path, char **args, char **envp)
{
	const bool	no_arg = (args[0] == NULL);

	if (no_arg)
		args[0] = path;
	execve(path, args, envp);
	if (no_arg)
		args[0] = NULL;
}

static void	child1_process(t_vars *vars, char **envp)
{
	close(vars->fd_out);
	close(vars->p_fd[0]);
	if (dup2(vars->fd_in, 0) == -1)
	{
		free_all(vars);
		close_files(vars, "ERROR : dup2 failed.\n");
	}
	if (dup2(vars->p_fd[1], 1) == -1)
	{
		free_all(vars);
		close_files(vars, "ERROR : dup2 failed.\n");
	}
	ft_execve(vars->cmd1, vars->all_cmd1, envp);
	free_all(vars);
	close(vars->fd_in);
	close(vars->p_fd[1]);
	error_management("pipex : Command not found.\n");
}

static void	child2_process(t_vars *vars, char **envp)
{
	close(vars->fd_in);
	close(vars->p_fd[1]);
	if (dup2(vars->p_fd[0], 0) == -1)
	{
		free_all(vars);
		close_files(vars, "ERROR : dup2 failed.\n");
	}
	if (dup2(vars->fd_out, 1) == -1)
	{
		free_all(vars);
		close_files(vars, "ERROR : dup2 failed.\n");
	}
	ft_execve(vars->cmd2, vars->all_cmd2, envp);
	free_all(vars);
	close(vars->fd_out);
	close(vars->p_fd[0]);
	error_management("pipex : Command not found.\n");
}

static void	parent_process(t_vars *vars, char **envp)
{
	vars->child2 = fork();
	if (vars->child2 == -1)
	{
		free_all(vars);
		close_files(vars, "ERROR : fork failed.\n");
	}
	if (!vars->child2 && vars->cmd2)
		child2_process(vars, envp);
	else
	{
		close(vars->fd_in);
		close(vars->fd_out);
		close(vars->p_fd[1]);
		close(vars->p_fd[0]);
		free_all(vars);
		while (waitpid(-1, NULL, 0) != -1)
			continue ;
	}
}

void	process(t_vars *vars, char **envp)
{
	vars->child1 = fork();
	if (vars->child1 == -1)
	{
		free_all(vars);
		close_files(vars, "ERROR : Fork failed.\n");
	}
	if (!vars->child1 && vars->cmd1)
		child1_process(vars, envp);
	else
		parent_process(vars, envp);
}

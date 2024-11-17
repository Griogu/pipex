/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpendilh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:53:10 by mpendilh          #+#    #+#             */
/*   Updated: 2024/11/17 10:36:23 by mpendilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	open_files(t_vars *vars, char **av)
{
	vars->fd_in = open(av[1], O_WRONLY);
	if (vars->fd_in == -1)
		error_management("ERROR : Infile can't be open.\n");
	vars->fd_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (vars->fd_out == -1)
	{
		close(vars->fd_in);
		error_management("ERROR : Outfile can't be open or create.\n");
	}
}

void	close_files(t_vars *vars, char *error_message)
{
	close(vars->fd_in);
	close(vars->fd_out);
	close(vars->p_fd[0]);
	close(vars->p_fd[1]);
	error_management(error_message);
}

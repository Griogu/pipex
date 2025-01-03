/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpendilh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:34:53 by mpendilh          #+#    #+#             */
/*   Updated: 2024/11/17 17:28:21 by mpendilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_vars	vars;

	if (ac != 5)
		error_management("ERROR : ./pipex infile cmd1 cmd2 outfile.\n");
	if (!envp || !envp[0])
		error_management("ERROR : No environment variable.\n");
	ft_memset((char *)&vars, 0, sizeof(t_vars));
	open_files(&vars, av);
	if (pipe(vars.p_fd) == -1)
	{
		close(vars.fd_in);
		close(vars.fd_out);
		error_management("ERROR : Pipe failed.\n");
	}
	vars.all_cmd1 = ft_split(av[2], ' ');
	if (!vars.all_cmd1)
		close_files(&vars, "pipex : Command not found.\n");
	vars.all_cmd2 = ft_split(av[3], ' ');
	if (!vars.all_cmd2)
	{
		free_tab(vars.all_cmd1);
		close_files(&vars, "pipex : Command not found.\n");
	}
	pipex(&vars, envp);
	return (0);
}

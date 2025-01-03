/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpendilh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:34:49 by mpendilh          #+#    #+#             */
/*   Updated: 2024/11/19 17:58:41 by mpendilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_variables
{
	pid_t	p_fd[2];
	pid_t	child1;
	pid_t	child2;
	int		fd_in;
	int		fd_out;

	char	*cmd1;
	char	*cmd2;
	char	**all_cmd1;
	char	**all_cmd2;

	char	*path;
	char	**all_path;
}	t_vars;

int		main(int ac, char **av, char **envp);
void	error_management(char *error_message);
void	open_files(t_vars *vars, char **av);
void	close_files(t_vars *vars, char *error_message);
void	pipex(t_vars *vars, char **envp);
char	*get_path(char **envp);
void	free_tab(char **tab);
void	free_all(t_vars *vars);
void	process(t_vars *vars, char **envp);

#endif

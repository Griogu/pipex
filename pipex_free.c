/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpendilh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:27:32 by mpendilh          #+#    #+#             */
/*   Updated: 2024/11/17 15:30:37 by mpendilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && (tab[i] || i == 0))
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_all(t_vars *vars)
{
	free(vars->cmd1);
	free(vars->cmd2);
	if (vars->all_cmd1)
		free_tab(vars->all_cmd1);
	if (vars->all_cmd2)
		free_tab(vars->all_cmd2);
}

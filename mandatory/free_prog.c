/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:14:47 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/16 11:28:28 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>

t_pipex	free_cmd_path(t_pipex pipex)
{
	int	i;

	i = 0;
	if (pipex.path)
		free(pipex.path);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	while (pipex.cmd_arg[i])
	{
		free(pipex.cmd_arg[i]);
		i++;
	}
	free(pipex.cmd_arg[i]);
	free(pipex.cmd_arg);
	close(pipex.pipe[0]);
	return (pipex);
}

void	free_parent(t_pipex *pipex)
{
	close(pipex->f_in);
	close(pipex->f_out);
}

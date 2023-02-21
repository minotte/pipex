/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:31:09 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/21 10:55:12 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/pipex_bonus.h" 

void	close_pipe_peer(t_pipex *pipex)
{
	close(pipex->pipe1[0]);
	close(pipex->pipe1[1]);
}

void	close_pipe_odd(t_pipex *pipex)
{
	close(pipex->pipe2[0]);
	close(pipex->pipe2[1]);
}

void	close_pipe_end(t_pipex *pipex, int argc)
{
	close(pipex->pipe1[1]);
	close(pipex->pipe1[0]);
	close(pipex->pipe2[1]);
	close(pipex->pipe2[0]);
}

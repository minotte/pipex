/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:28:07 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/21 10:32:45 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/pipex_bonus.h"
#include <sys/wait.h>
#include <unistd.h>

t_pipex	child_start(t_pipex pipex, t_path path, char **argv)
{
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	dup2(pipex.f_in, STDIN_FILENO);
	close(pipex.f_in);
	close(pipex.f_out);
	path.cmd_arg = ft_split(argv[2], ' ');
	path.path = ft_access_cmd(path.env, path.cmd_arg[0]);
	if (!path.path)
	{
		if (argv[2][0] == '\0')
			ft_putendl_fd("command \"\" not found", 2);
		else
			perror("error, fonction");
		free_cmd_path(path);
		exit(127);
	}
	else
	{
		path.cmd_arg[0] = ft_strrchr_pipex(path.cmd_arg[0], '/');
		path.cmd_arg[0] = ft_strtrim(path.cmd_arg[0], "/");
		execve(path.path, path.cmd_arg, path.env);
	}
}

t_pipex	child_end(t_pipex pipex, t_path path, char **argv)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	close(pipex.pipe[0]);
	dup2(pipex.f_out, 1);
	close(pipex.f_in);
	close(pipex.f_out);
	path.cmd_arg = ft_split(argv[3], ' ');
	path.path = ft_access_cmd(path.env, path.cmd_arg[0]);
	if (!path.path)
	{
		if (argv[3][0] == '\0')
		{
			ft_putendl_fd("command \"\" not found", 2);
			free_cmd_path(path);
			exit(126);
		}
		perror("error, first fonction");
		free_cmd_path(path);
		exit(127);
	}
	else
	{
		path.cmd_arg[0] = ft_strrchr_pipex(path.cmd_arg[0], '/');
		path.cmd_arg[0] = ft_strtrim(path.cmd_arg[0], "/");
		execve(path.path, path.cmd_arg, path.env);
	}
}

t_pipex	child_loop(t_pipex pipex, int index, t_path path, char **argv)
{
	if (index % 2)
	{
		dup2(pipex.pipe[0], pipex.pipe2[1]);
		dup
		close_pipe_odd(,);
		

	}
	else if (index % 2)
	{
		dup2(pipex.pipe[0], pipex.pipe2[1]);
		close_pipe_peer(,);


	}
	
	waitpid(pipex.pid, NULL, 0);
	return (pipex);
}

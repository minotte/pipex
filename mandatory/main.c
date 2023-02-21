/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:37:48 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/17 10:50:52 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

void	ft_child_first(t_pipex pipex, char **argv)
{
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	dup2(pipex.f_in, STDIN_FILENO);
	close(pipex.f_in);
	close(pipex.f_out);
	pipex.cmd_arg = ft_split(argv[2], ' ');
	pipex.path = ft_access_cmd(pipex.env, pipex.cmd_arg[0]);
	if (!pipex.path)
	{
		if (argv[2][0] == '\0')
			ft_putendl_fd("command \"\" not found", 2);
		else
			perror("error, first fonction");
		free_cmd_path(pipex);
		exit(127);
	}
	else
	{
		pipex.cmd_arg[0] = ft_strrchr_pipex(pipex.cmd_arg[0], '/');
		pipex.cmd_arg[0] = ft_strtrim(pipex.cmd_arg[0], "/");
		execve(pipex.path, pipex.cmd_arg, pipex.env);
	}
}

void	ft_child_sec(t_pipex pipex, char **argv)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	close(pipex.pipe[0]);
	dup2(pipex.f_out, 1);
	close(pipex.f_in);
	close(pipex.f_out);
	pipex.cmd_arg = ft_split(argv[3], ' ');
	pipex.path = ft_access_cmd(pipex.env, pipex.cmd_arg[0]);
	if (!pipex.path)
	{
		if (argv[3][0] == '\0')
		{
			ft_putendl_fd("command \"\" not found", 2);
			free_cmd_path(pipex);
			exit(126);
		}
		perror("error, first fonction");
		free_cmd_path(pipex);
		exit(127);
	}
	else
	{
		pipex.cmd_arg[0] = ft_strrchr_pipex(pipex.cmd_arg[0], '/');
		pipex.cmd_arg[0] = ft_strtrim(pipex.cmd_arg[0], "/");
		execve(pipex.path, pipex.cmd_arg, pipex.env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int			status;

	if (argc != 5)
	{
		ft_putendl_fd ("I need 4 arguments like this:file1 cmd1 cmd2 file2", 2);
		return (1);
	}
	pipex.f_in = open(argv[1], O_RDONLY);
	if (pipex.f_in < 0)
		perror("Error : ");
	pipex.f_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 00666);
	if (pipex.f_out < 0)
	{
		ft_putstr_fd("Error : ", 2);
		perror(argv[4]);
		exit (1);
	}
	pipex.env = envp;
	if (pipe(pipex.pipe) == -1)
	{
		perror("Error : pipe");
		return (2);
	}
	if (pipex.f_in > 0)
	{
		pipex.pid1 = fork();
		if (pipex.pid1 == 0)
			ft_child_first(pipex, argv);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		ft_child_sec(pipex, argv);
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	if (pipex.f_in > 0)
	{
		waitpid(pipex.pid1, NULL, 0);
	}
	waitpid(pipex.pid2, &status, 0);
	free_parent(&pipex);
	if (WIFEXITED(status))
		printf("exited, status=%d\n", WEXITSTATUS(status));

	return (WEXITSTATUS(status));
}

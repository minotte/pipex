/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:37:48 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/13 18:13:45 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/print/ft_printf.h"
#include "libft/str/ft_str.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_child_first(t_pipex pipex, char **argv, int i)
{
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
//	close(pipex.pipe[1]);
	dup2(pipex.f_in, STDIN_FILENO);
//	close(pipex.f_in);
//	close(pipex.f_out);
	pipex.cmd_arg = ft_split(argv[i], ' ');
	pipex.path = ft_access_cmd(pipex.env, pipex.cmd_arg[0]);
	if (pipex.path)
		execve(pipex.path, pipex.cmd_arg, pipex.env);
	else
	{
		ft_putendl_fd("error,ghj fction not found", 2);

	}
}

void	ft_child_sec(t_pipex pipex, char **argv, int i)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	
	i = 0;
	dup2(pipex.f_out, 1);
//	close(pipex.f_in);
//	close(pipex.f_out);

	pipex.cmd_arg = ft_split(argv[3], ' ');
	pipex.path = ft_access_cmd(pipex.env, pipex.cmd_arg[0]);
	printf("path : %s", pipex.path);
//	close(pipex.pipe[0]);
	if (pipex.path)
		execve(pipex.path, pipex.cmd_arg, pipex.env);
	else
	{
		ft_putendl_fd("error, fction not found", 2);
		//free_cmd_path(pipex);
	}
}

/*void	ft_pipex(t_pipex pipex)
{
	close(pipex.pipe[0]);
	dup2(pipex.f_out, STDOUT_FILENO);
	dup2(pipex.pipe[1], STDIN_FILENO);
	close(pipex.pipe[1]);
}*/
/*
t_pipex	ft_arg(t_pipex pipex, int index, char **argv)
{
	char	**arg;

	arg = ft_split(argv[index], ' ');
	pipex.cmd_arg[index] = *arg;
	pipex.path = ft_access_cmd(pipex.env);
	return (pipex);
}
*/
int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	pipex;

	i = 2;
	if (argc != 5)
	{
		ft_putendl_fd ("I need 4 arguments like this:file1 cmd1 cmd2 file2", 2);
		return (1);
	}
	pipex.f_in = open(argv[1], O_RDONLY);
	if (pipex.f_in < 0)
	{
		perror("Error : ");
		i++;
	}
	pipex.f_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 00666);
	if (pipex.f_out < 0)
		perror("Error : ");
	pipex.env = envp;
	if (pipe(pipex.pipe) == -1)
	{
		perror("Error : pipe");
		return (2);
	}
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		ft_child_first(pipex, argv, i);
	i++;
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		ft_child_sec(pipex, argv, i);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	
	return (0);
}

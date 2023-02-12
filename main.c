/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:37:48 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/03 17:42:57 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

void	ft_child_first(t_pipex pipex)
{
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
	dup2(pipex.f_in, 0);
	pipex arg
	if (pipex arg)
		execve(pipe cmd, args , pipex.env);
}

void	ft_child_sec(t_pipex pipex)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	dup2(pipex.f_out, 1);
	pipex arg
	if (pipex arg)
		execve(pipe cmd, args , pipex.env);
}

void	ft_pipex(t_pipex pipex)
{

}

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
		perror("Error : ");
	pipex.f_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC);
	if (pipex.f_out < 0)
		perror("Error : ");
	pipex.env = envp;
	if (pipe(pipex.pipe) == 0)
		perror("pipe :");
	while (i < argc)
	{
		pipex.cmd_arg[i] = ft_split(argv[i], ' ');
		pipex.path = ft_access_cmd(pipex.cmd_arg, envp);
		i++;
	}
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		ft_child_first(pipex);
	pipex.pid2 = fork();
		ft_child_sec(pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}

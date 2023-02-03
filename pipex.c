/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:32:50 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/02 19:10:15 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "libft/print/ft_printf.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int	ft_child_pid(int *pipefd)
{
	close(pipefd[1]);
//	ft_putendl_fd("teST", 1);
	close(pipefd[0]);
	return (0);
}

int	ft_parent_pid(int *pipefd, int argc, char **argv, char **envp)
{
	int		i;
	char	*buf;

	dup2(f1, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);

	dup2(f2, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	read(f1, buf, 10);
	i = 1;
	close(pipefd[0]);
	while (i < arint	i;gc)
	{
		parsing(argv, i, envp);
		i++;
	}
	close(pipefd[1]);
	wait(NULL);
	return (0);
}

void	pipex(int f1, int f2)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("Error : pipe");
		return (2);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error fork :");
		return (4);
	}
	if (pid != 0)
		pid = fork();
	else if (pid == 0)
		ft_child_pid(pipefd);
	else
		ft_parent_pid(pipefd, argc, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	f1;
	int	f2;

	if (argc != 5)
	{
		ft_putendl_fd ("I need 4 arguments like this:file1 cmd1 cmd2 file2", 2);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (i == 1)
		{
			f1 = open(argv[i], O_CREAT | O_RDWR);
			if (f1 == -1)
				i++;
		}
		else if (i == argc - 1)
			f2 = open(argv[i], O_CREAT | O_RDWR | O_TRUNC);
		else
			parsing(argv, i, envp);
		i++;
	}
	return (0);
}

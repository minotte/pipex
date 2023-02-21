/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:05:52 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/20 18:31:07 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		heredc;
	int		status;
	t_pipex	pipex;
	t_path	path;

	heredc = ft_strcmp_str(argv[1], "here_doc");
	if (argc <= (3 + heredc))
	{
		ft_putendl_fd("need more arguments", 2);
		return (1);
	}
	if (pipe(pipex.pipe) == -1)
		ft_error_pipe();
	if (heredc)
		pipex = ft_heredoc(argv[2], pipex);
	else
	{
		pipex.f_in = open(argv[1], O_RDWR);
		if (pipex.f_in < 0)
			perror("Error : ");
	}
	pipex.f_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 00666);
	if (pipex.f_out < 0)
	{
		ft_putstr_fd("Error: ", 2);
		perror(argv[argc - 1]);
		exit (1);
	}
	path.env = envp;
	i = 2 + heredc;
	while (i < (argc - 1))
	{
		if (i == (2 + heredc))
			child_start(pipex, path, argv);
		else if (i == (argc - 2))
			child_end(pipex, path, argv);
		child_loop(pipex, i, path, argv);
		i++;
	}
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	close_fd(&pipex);
	return (WEXITSTATUS(status));
}

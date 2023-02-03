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

void	ft_child(t_pipex pipex)
{
	dup2(int __fd, int __fd2);

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
	while (i < argc)
	{
		pipex.cmd_arg[i] = ft_split(argv[i], ' ');
		pipex.path = ft_access_cmd(pipex.cmd_arg, envp);
		i++;
	}
	pipex.pid = fork();
	if (pipex.pid == 0)
		ft_child(pipex);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:08:14 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/15 10:21:02 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
#include <stdlib.h>

typedef struct s_pipex
{
	int		f_in;
	int		f_out;
	int		pipe[2];
	char	**cmd_arg;
	char	*path;
	char	**env;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

int		main(int argc, char **argv, char **envp);
char	*ft_access_cmd(char **env, char *arg);
t_pipex	free_cmd_path(t_pipex pipex);
void	free_parent(t_pipex *pipex);

#endif

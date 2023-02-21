/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:11:50 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/17 18:21:37 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		f_in;
	int		f_out;
	int		argc;
	int		pipe1[2];
	int		pipe2[2];
	pid_t	pid;
}	t_pipex;

typedef struct s_path
{
	char	**cmd_arg;
	char	*path;
	char	**env;
}	t_path;

int		main(int argc, char **argv, char **envp);
t_pipex	child_start(t_pipex pipex, t_path path, char **argv);
t_pipex	child_end(t_pipex pipex, t_path path, char **argv);
void	close_pipe_end(t_pipex *pipex, int argc);
void	close_fd(t_pipex *pipex);
t_pipex	ft_heredoc(char *eof, t_pipex pipex);
void	ft_error_pipe(void);
t_pipex	child_loop(t_pipex pipex, int index, char **argv, char **env);
//char	*ft_access_cmd(char **env, char *arg);
t_pipex	free_cmd_path(t_pipex pipex, t_path path);
//void	free_parent(t_pipex *pipex);

#endif

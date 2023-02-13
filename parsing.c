/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:39:36 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/13 17:54:12 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

t_pipex	free_cmd_path(t_pipex pipex)
{
	int	i;

	i = 0;
	//free(pipex.path);
	while (pipex.cmd_arg[i])
	{
		free(pipex.cmd_arg[i]);
		i++;
	}
	free(pipex.cmd_arg);
	return (pipex);
}

char	**ft_path(char **env)
{
	char	*path;
	char	**epath;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path = ft_strtrim(env[i], "PATH=");
	epath = ft_split(path, ':');
	free(path);
	return (epath);
}

char	*ft_access_cmd(char **env, char *arg)
{
	char	**path;
	char	*thepath;
	int		i;
	int		result;

	i = 0;
	thepath = NULL;
	path = NULL;
	path = ft_path(env);
	while (path[i])
	{
		path[i] = ft_strjoin_free(path[i], "/");
		path[i] = ft_strjoin_free(path[i], arg);

	/*	if (!arg)
			path[i] = ft_strjoin_free(path[i], argv);*/
		result = access(path[i], X_OK);
		if (result == 0)
		{
			thepath = ft_strdup(path[i]);
			while (path[i])
			{
				free(path[i]);
				i++;
			}
			break ;
		}
		free(path[i]);
		i++;
	}
//	printf("\nresult = %s\n result = %d \n", thepath, access(thepath, X_OK));
	free(path);
//	printf("\n\the path is %s\n", thepath);
	return (thepath);
}
/*
int	parsing(char **argv, int index, char **env)
{
	char	*path;
	char	**arg;
	int		i;

	arg = NULL;
	path = NULL;
	arg = ft_split(argv[index], ' ');
	path = ft_access_cmd(arg[0], env);
	printf("\nresult = %s\n", path);
	if (path)
		execve(path, arg, env);
	i = 0;

	if (arg)
	{
		while (arg[i])
		{
			free(arg[i]);
			i++;
		}
	}
	free(arg);
	free(path);
	return (0);
}*/

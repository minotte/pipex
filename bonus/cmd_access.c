/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:12:26 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/21 10:36:04 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/pipex_bonus.h"

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
	if (!arg)
		return (NULL);
	if (!(ft_strchr(arg, '/')))
	{
		path = ft_path(env);
		while (path[i])
		{
			path[i] = ft_strjoin_free(path[i], "/");
			path[i] = ft_strjoin_free(path[i], arg);
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
	}
	else
	{
		result = access(arg, X_OK);
		if (result == 0)
			thepath = arg;
	}
	if (path)
		free(path);
	return (thepath);
}

t_pipex	free_cmd_path(t_pipex pipex, t_path path)
{
	int	i;

	i = 0;
	if (path.path)
		free(path.path);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	while (path.cmd_arg[i])
	{
		free(path.cmd_arg[i]);
		i++;
	}
	free(path.cmd_arg[i]);
	free(path.cmd_arg);
	close(pipex.pipe[0]);
	return (pipex);
}

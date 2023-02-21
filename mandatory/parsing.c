/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:39:36 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/16 12:12:21 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

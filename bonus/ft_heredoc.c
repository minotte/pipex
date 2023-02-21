/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nminotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:42:18 by nminotte          #+#    #+#             */
/*   Updated: 2023/02/17 19:10:00 by nminotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include  "../include/pipex_bonus.h"
#include <stdlib.h>
#include <unistd.h>

t_pipex	ft_heredoc(char *eof, t_pipex pipex)
{
	char	*line;

	eof = ft_strjoin(eof, "\n");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_line_stdin(0);
	//	printf("%s", line);
		write(pipex.pipe[1], line, ft_strlen(line));
		
		if (ft_strcmp_str(line, eof))
		{
			free(line);
			break ;
		}
		free(line);
	}
	free(eof);
	return (pipex);
}

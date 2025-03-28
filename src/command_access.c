/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 00:47:45 by mbico             #+#    #+#             */
/*   Updated: 2024/04/14 19:48:00 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_justpath(char *cmd, char **adr)
{
	if (!(access(cmd, F_OK) || access(cmd, X_OK)))
	{
		*adr = ft_strdup(cmd);
		return (1);
	}
	return (0);
}

int	ft_command_checker(t_data *data, char *cmd, char **adr, t_bool last)
{
	char	**path_ptr;
	char	*path;

	path_ptr = data->cmd_path;
	if (ft_justpath(cmd, adr))
		return (0);
	while ((access(cmd, F_OK) || access(cmd, X_OK)) && path_ptr && *path_ptr)
	{
		path = ft_strjoin(*path_ptr, cmd);
		if (!path)
			return (1);
		if (access(path, F_OK) || access(path, X_OK))
			free(path);
		else
		{
			*adr = path;
			return (0);
		}
		path_ptr ++;
	}
	if (!(!last && data->infile == -1))
		perror(cmd);
	return (0);
}

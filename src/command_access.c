/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 00:47:45 by mbico             #+#    #+#             */
/*   Updated: 2024/03/12 16:04:26 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_command_checker(t_data *data, char *cmd, char **adr)
{
	char	**path_ptr;
	char	*path;

	path_ptr = data->cmd_path;
	if (!(access(cmd, F_OK) || access(cmd, X_OK)))
	{
		*adr = cmd;
		return;
	}
	while (*path_ptr)
	{
		path = ft_strjoin(*path_ptr, cmd);
		if (!path)
			data->error = TRUE;
		if (access(path, F_OK) || access(path, X_OK))
			free(path);
		else
		{
			*adr = path;
			return;
		}
		path_ptr ++;
	}
	perror(cmd);
	data->error = TRUE;
}

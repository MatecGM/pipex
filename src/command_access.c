/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 00:47:45 by mbico             #+#    #+#             */
/*   Updated: 2024/03/11 18:29:02 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_command_checker(t_data *data, char *command, char **adr)
{
	char	**path_ptr;
	char	*path;
	char	*name;

	path_ptr = data->cmd_path;
	name = ft_quote_delimiter(command);
	ft_printf("la -> %s\n", ft_quote_delimiter(command));
	while (*path_ptr)
	{
		path = ft_strjoin(*path_ptr, name);
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
	if (!(access(name, F_OK) || access(name, X_OK)))
		*adr = path;
	else
	{
		perror(name);
		data->error = TRUE;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 00:47:45 by mbico             #+#    #+#             */
/*   Updated: 2024/03/30 14:30:48 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_command_splitter(t_data *data, char **argv, int argc)
{
	int		i;
	char	**parsed_cmd;
	t_list	*new;

	i = 2;
	data->cmd = NULL;
	while (i < argc - 1)
	{
		parsed_cmd = ft_split_quote(argv[i], data);
		new = ft_lstnew(parsed_cmd);
		ft_lstadd_back(&data->cmd, new);
		if (!new || !parsed_cmd)
		{
			ft_putstr_fd("malloc: allocation error", 2);
			ft_close(TRUE, data);
		}
		i ++;
	}
}

int	ft_command_check_stock(t_data *data, char *cmd, char **adr, t_bool last)
{
	char	**path_ptr;
	char	*path;

	path_ptr = data->path;
	if (!(access(cmd, F_OK) || access(cmd, X_OK)))
		*adr = cmd;
	while ((access(cmd, F_OK) || access(cmd, X_OK)) && *path_ptr)
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
	perror(cmd);
	if (last)
		data->error = TRUE;
	return (0);
}

t_bool	ft_commande_stocker(t_data *data, int argc)
{
	int		i;
	t_list	*ptr;
	char	**cmd;
	t_bool	last;

	data->path_cmd = ft_calloc(sizeof(char *), argc - 2);
	if (!data->path_cmd)
		return (TRUE);
	i = 2;
	ptr = data->cmd;
	last = FALSE;
	while (i < argc - 1 && ptr)
	{
		cmd = ptr->content;
		if (i == argc - 2)
			last = TRUE;
		if (ft_command_check_stock(data, cmd[0], &data->path_cmd[i - 2], last))
			return (TRUE);
		ptr = ptr->next;
		i ++;
	}
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:49:11 by mbico             #+#    #+#             */
/*   Updated: 2024/04/03 18:34:39 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close(t_bool error, t_data *data)
{
	ft_free_tab(data->path);
	ft_free_tab(data->cmd1);
	ft_free_tab(data->cmd2);
	free(data->path_cmd1);
	free(data->path_cmd2);
	if (error)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	ft_file_open(t_data *data, char *infile, char *outfile)
{
	if (access(infile, F_OK) || access(infile, R_OK))
	{
		perror(infile);
		data->error = TRUE;
	}
	if (!access(outfile, F_OK) && access(outfile, W_OK))
	{
		perror(outfile);
		data->error = TRUE;
	}
	data->infile = open(infile, O_RDONLY);
	if (!data->infile)
	{
		perror(infile);
		data->error = TRUE;
	}
}

int	ft_cmd_path(t_data *data, char **env)
{
	char	**line;
	char	*tmp;

	line = env;
	data->path = NULL;
	while (line && *line)
	{
		if (!ft_strncmp(*line, "PATH=", 5))
		{
			data->path = ft_split(*line + 5, ':');
			line = data->path;
			while (data->path && *line)
			{
				tmp = *line;
				*line = ft_strjoin(tmp, "/");
				free(tmp);
				if (!*line)
					return (1);
				line ++;
			}
			return (0);
		}
		line ++;
	}
	return (1);
}

void	ft_datainit(t_data *data, char **env, int argc, char **argv)
{
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->path_cmd1 = NULL;
	data->path_cmd2 = NULL;
	data->cmd = NULL;
	data->path_cmd = NULL;
	data->error = FALSE;
	if (ft_cmd_path(data, env) || !data->path)
		ft_close(TRUE, data);
	ft_file_open(data, argv[1], argv[argc - 1]);
	if (data->error)
		ft_close(data->error, data);
	ft_command_splitter(data, argv, argc);
	if (ft_commande_stocker(data, argc))
	{
		ft_putstr_fd("malloc: allocation error", 2);
		ft_close(TRUE, data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data[1];

	if (TRUE)
		return (0);
	if ((argc < 5))
	{
		ft_putstr_fd("argv: incorrect arg number\n", 2);
		return (1);
	}
	ft_datainit(data, env, argc, argv);
	if (data->error)
		ft_close(data->error, data);
	ft_pipex(data, env, argv[argc - 1], argc);
	ft_close(data->error, data);
}

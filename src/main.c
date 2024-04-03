/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:49:11 by mbico             #+#    #+#             */
/*   Updated: 2024/04/03 18:33:13 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(t_bool error, t_data *data)
{
	ft_free_tab(data->cmd_path);
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
	else if (data->error)
	{
		data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(data->outfile);
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
	data->cmd_path = NULL;
	while (line && *line)
	{
		if (!ft_strncmp(*line, "PATH=", 5))
		{
			data->cmd_path = ft_split(*line + 5, ':');
			line = data->cmd_path;
			while (data->cmd_path && *line)
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

void	ft_datainit(t_data *data, char **argv, char **env)
{
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->path_cmd1 = NULL;
	data->path_cmd2 = NULL;
	data->error = FALSE;
	if (ft_cmd_path(data, env) || !data->cmd_path)
		ft_close(TRUE, data);
	ft_file_open(data, argv[1], argv[4]);
	if (data->error)
		ft_close(data->error, data);
	data->cmd1 = ft_split_quote(argv[2], data);
	data->cmd2 = ft_split_quote(argv[3], data);
	if (!data->cmd1 || !data->cmd2
		|| ft_command_checker(data, data->cmd1[0], &data->path_cmd1, FALSE)
		|| ft_command_checker(data, data->cmd2[0], &data->path_cmd2, TRUE))
	{
		ft_putstr_fd("malloc: allocation error", 2);
		ft_close(TRUE, data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data[1];

	if (argc != 5)
	{
		ft_putstr_fd("argv: incorrect arg number\n", 2);
		return (1);
	}
	ft_datainit(data, argv, env);
	if (data->error)
		ft_close(data->error, data);
	ft_pipex(data, env, argv[4]);
	ft_close(data->error, data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:49:11 by mbico             #+#    #+#             */
/*   Updated: 2024/03/18 19:26:52 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(t_bool error)
{
	if (error)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
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
	while (line)
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


int	main(int argc, char **argv, char **env)
{
	t_data	data[1];

	data->error = FALSE;
	if ((argc != 5) || ft_cmd_path(data, env) || !data->cmd_path)
		ft_close(1);
	ft_file_open(data, argv[1], argv[4]);
	if (data->error)
		ft_close(1);
	data->cmd1 = ft_split_quote(argv[2]);
	data->cmd2 = ft_split_quote(argv[3]);
	ft_command_checker(data, data->cmd1[0], &data->path_cmd1);
	ft_command_checker(data, data->cmd2[0], &data->path_cmd2);
	if (data->error)
		ft_close(1);
	test(data, env, argc, argv[4]);
	return (0);
}

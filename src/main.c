/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:49:11 by mbico             #+#    #+#             */
/*   Updated: 2024/03/11 16:26:11 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int error)
{
	if (error)
	{
		ft_putstr_fd("ERROR\n", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}

void	ft_file_open(t_data *data, char *infile, char *outfile)
{
	if (access(infile, F_OK) || access(infile, X_OK))
	{
		perror(infile);
		data->error = TRUE;
	}
	if (!access(outfile, F_OK) && access(outfile, X_OK))
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

	ft_printf("%s\n", ft_quote_delimiter("test t"));
	//if (ft_cmd_path(data, env) || !data->cmd_path)
	// 	ft_close(1);
	ft_printf("%s\n", ft_quote_delimiter("test t"));
	ft_file_open(data, argv[1], argv[4]);
	ft_command_checker(data, argv[2], &data->cmd1);
	ft_command_checker(data, argv[3], &data->cmd2);
	ft_printf("cmd 1 = %s et cmd 2 = %s\n", data->cmd1, data->cmd2);
	if (argc != 5)
	  	ft_close(1);
}

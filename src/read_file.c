/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:20:18 by mbico             #+#    #+#             */
/*   Updated: 2024/03/18 19:36:51 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	test(t_data *data, char **env, int argc, char *outfile)
{
	int	pid[2];
	int	fd[2];
	int	tmp;

	if (pipe(fd) == -1)
		return ;
	pid[0] = fork();
	tmp = dup(1);
	if (pid[0] == 0)
	{
		dup2(data->infile, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(data->path_cmd1, data->cmd1, env);
	}
	pid[1] = fork();
	data->outfile = open(outfile, O_WRONLY | O_CREAT, 0644);
	if (pid[1] == 0)
	{
		dup2(fd[0], 0);
		dup2(data->outfile, 1);
		close(fd[0]);
		close(fd[1]);
		execve(data->path_cmd2, data->cmd2, env);
	}
}

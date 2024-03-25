/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:20:18 by mbico             #+#    #+#             */
/*   Updated: 2024/03/25 14:09:49 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	firstcmd(t_data *data, int *fd, char **env)
{
	int pid;

	if (data->path_cmd1)
		pid = fork();
	if (!pid)
	{
		dup2(data->infile, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(data->infile);
		if (!execve(data->path_cmd1, data->cmd1, env))
		{
			perror(data->cmd1[0]);
			data->error = TRUE;
		}
	}
	return (pid);
}

int	lastcmd(t_data *data, int *fd, char **env, char *outfile)
{
	int pid;

	data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (!pid)
	{
		dup2(fd[0], 0);
		dup2(data->outfile, 1);
		close(fd[0]);
		close(fd[1]);
		close(data->infile);
		close(data->outfile);
		if (!execve(data->path_cmd2, data->cmd2, env))
		{
			perror(data->cmd2[0]);
			data->error = TRUE;
		}
	}
	return (pid);
}

void	pipex(t_data *data, char **env, char *outfile)
{
	int	pid1;
	int	pid2;
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	pid1 = firstcmd(data, fd, env);
	pid2 = lastcmd(data, fd, env, outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

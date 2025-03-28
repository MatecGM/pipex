/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:20:18 by mbico             #+#    #+#             */
/*   Updated: 2024/04/14 22:02:38 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	firstcmd(t_data *data, int *fd, char **env)
{
	int	pid;

	pid = -1;
	if (data->path_cmd1 && data->infile != -1)
		pid = fork();
	if (!pid)
	{
		dup2(data->infile, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		if (data->infile != -1)
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
	int	pid;

	close(fd[1]);
	pid = -1;
	data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->path_cmd2)
	{
		pid = fork();
	}
	if (!pid)
	{
		dup2(fd[0], 0);
		dup2(data->outfile, 1);
		close(fd[0]);
		close(fd[1]);
		if (data->infile != -1)
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

void	ft_pipex(t_data *data, char **env, char *outfile)
{
	int	fd[2];
	int	pid[2];

	if (pipe(fd) == -1)
	{
		perror("pipe:");
		data->error = TRUE;
		return ;
	}
	pid[0] = firstcmd(data, fd, env);
	pid[1] = lastcmd(data, fd, env, outfile);
	close(fd[0]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
}

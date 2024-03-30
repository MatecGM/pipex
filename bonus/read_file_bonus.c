/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:20:18 by mbico             #+#    #+#             */
/*   Updated: 2024/03/30 17:47:23 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	*firstcmd(t_data *data, char **env, char *path_cmd, char **cmd)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		return (0);
	pid = -1;
	if (path_cmd)
		pid = fork();
	if (!pid)
	{
		dup2(data->infile, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(data->infile);
		if (!execve(path_cmd, cmd, env))
		{
			perror(cmd[0]);
			data->error = TRUE;
		}
	}
	return (fd);
}

void	lastcmd(t_data *data, int *fd, char **env, char *outfile)
{
	int	pid;

	data->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!execve(data->path_cmd2, data->cmd2, env))
	{
		perror(data->cmd2[0]);
		data->error = TRUE;
		return ;
	}
	close(fd[1]);
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
}

void	ft_pipex(t_data *data, char **env, char *outfile, int argc)
{
	int		fd[2];
	int		i;
	t_list	*ptr;

	ptr = data->cmd;
	i = 0;
	while (i < argc - 3)
	{
		if (i == argc - 4)
			lastcmd(data, fd, env, outfile);
		else
			fd = firstcmd(data, env, data->path_cmd[i], ptr->content);
		i ++;
		ptr = ptr->next;
	}
	lastcmd(data, fd, env, outfile);
	wait(NULL);
	wait(NULL);
	close(fd[0]);
	close(data->infile);
	close(data->outfile);
}

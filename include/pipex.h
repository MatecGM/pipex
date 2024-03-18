/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:55:04 by mbico             #+#    #+#             */
/*   Updated: 2024/03/18 17:21:25 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define MALLOC_FAILURE "the malloc failed"

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
#include <sys/wait.h>

typedef struct s_data
{
	int		infile;
	int		outfile;
	char	**cmd1;
	char	*path_cmd1;
	char	**cmd2;
	char	*path_cmd2;
	char	**all_cmd_path;

	char	**cmd_path;
	t_bool	error;
}	t_data;


void	ft_close(int error);
char	**ft_split_quote(char *str);
void	ft_command_checker(t_data *data, char *cmd, char **adr);
void	test(t_data *data, char **env, int argc, char *outfile);

#endif
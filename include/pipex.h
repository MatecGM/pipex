/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:55:04 by mbico             #+#    #+#             */
/*   Updated: 2024/03/12 15:59:42 by mbico            ###   ########.fr       */
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

typedef struct s_data
{
	int		infile;
	int		outfile;
	char	**cmd1;
	char	*path_cmd1;
	char	**cmd2;
	char	*path_cmd2;

	char	**cmd_path;
	t_bool	error;
}	t_data;


void	ft_close(int error);
char	**ft_split_quote(char *str);
void	ft_command_checker(t_data *data, char *cmd, char **adr);

#endif
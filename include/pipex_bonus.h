/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:55:04 by mbico             #+#    #+#             */
/*   Updated: 2024/03/30 15:07:42 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include <sys/wait.h>

typedef struct s_data
{
	int		infile;
	int		outfile;
	char	**cmd1;
	char	*path_cmd1;
	char	**cmd2;
	char	*path_cmd2;

	char	**path_cmd;
	t_list	*cmd;
	char	**path;
	t_bool	error;
}	t_data;

void	ft_close(int error, t_data *data);
char	**ft_split_quote(char *str, t_data *data);
void	ft_pipex(t_data *data, char **env, char *outfile, int argc);
void	ft_free_tab(char **splitted_char);
void	ft_command_splitter(t_data *data, char **argv, int argc);
t_bool	ft_commande_stocker(t_data *data, int argc);

#endif
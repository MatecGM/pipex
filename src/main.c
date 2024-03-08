/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:49:11 by mbico             #+#    #+#             */
/*   Updated: 2024/03/08 19:20:22 by mbico            ###   ########.fr       */
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

int	ft_file_checker(char *file)
{
	if (access(file, F_OK) || access(file, X_OK))
	{
		perror(file);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	//t_data	*data;

	ft_file_checker(argv[1]);
	(void) env;
	if (argc != 4)
		ft_close(1);
}

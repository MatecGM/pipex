/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:49:11 by mbico             #+#    #+#             */
/*   Updated: 2024/03/08 18:11:02 by mbico            ###   ########.fr       */
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

void	ft_file_checker(char *file)
{
	
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc != 4)
		ft_close(1);
	
}

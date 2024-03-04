/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:49:11 by mbico             #+#    #+#             */
/*   Updated: 2024/03/04 14:38:43 by mbico            ###   ########.fr       */
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

void	check_input(int argc, char **argv, char **env)
{
	(void) argv;
	if (argc != 4)
		ft_close(1);
	execve(argv[1], argv + 1, env);
}

int	main(int argc, char **argv, char **env)
{
	check_input(argc, argv, env);
	ft_close(0);
}

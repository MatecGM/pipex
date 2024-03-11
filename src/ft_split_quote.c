/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:30:55 by mbico             #+#    #+#             */
/*   Updated: 2024/03/11 18:46:05 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freeall(char **splitted_char, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(splitted_char[i]);
		i ++;
	}
	free(splitted_char);
}

char	**ft_realloc(char **tab)
{
	int		len;
	char	**dst;
	int		i;

	len = 0;
	while (tab[len])
		len++;
	dst = ft_calloc(sizeof(char), len + 1);
	i = 0;
	while (tab)
}

char	**ft_split_quote(char *str)
{
	while ()
}

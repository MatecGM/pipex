/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:30:55 by mbico             #+#    #+#             */
/*   Updated: 2024/03/12 15:05:29 by mbico            ###   ########.fr       */
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
	while (tab && tab[len])
		len++;
	dst = ft_calloc(sizeof(char *), len + 2);
	if (!dst)
	{
		ft_freeall(tab, len);
		return (NULL);
	}
	i = 0;
	while (tab && dst && tab[i])
	{
		dst[i] = tab[i];
		i++;
	}
	if (tab)
		free(tab);
	return (dst);
}

int	ft_quote_len(char *str)
{
	t_bool	quote;
	t_bool	single;
	int		len;

	quote = FALSE;
	len = 0;
	while (*str && !(*str == ' ' && !quote))
	{
		if (*str == '\'' && !quote)
			single = TRUE;
		else if (*str == '"' && !quote)
			single = FALSE;
		if (*str == '\'' || *str == '"')
			quote = !quote;
		else
			len ++;
		str ++;
	}
	return (len);
}

char	*ft_word_filler(char *src, char *dst)
{
	t_bool	quote;
	t_bool	single;
	int		i;

	quote = FALSE;
	i = 0;
	while (dst && *src && !(*src == ' ' && !quote))
	{
		if (*src == '\'' && !quote)
			single = TRUE;
		else if (*src == '"' && !quote)
			single = FALSE;
		if (*src == '\'' || *src == '"')
			quote = !quote;
		else
			dst[i++] = *src;
		src ++;
	}
	if (!*src && quote)
	{
		ft_putstr_fd("Error: unclosed quote\n", 2);
		ft_close(TRUE);
	}
	return (src);
}

char	**ft_split_quote(char *str)
{
	char	**cmd;
	int		j;
	int		len;

	cmd = NULL;
	j = 0;
	while (*str)
	{
		len = ft_quote_len(str);
		cmd = ft_realloc(cmd);
		if (!cmd)
			return (NULL);
		cmd[j] = ft_calloc(sizeof(char), len + 1);
		str = ft_word_filler(str, cmd[j]);
		if (!cmd[j] || !str)
		{
			ft_freeall(cmd, j);	
			return (NULL);
		}
		if (*str)
			str ++;
		j++;
	}
	return (cmd);
}

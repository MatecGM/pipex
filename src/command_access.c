/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 00:47:45 by mbico             #+#    #+#             */
/*   Updated: 2024/03/11 16:27:11 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_quote_len(char *str)
{
	int		len;
	t_bool	quote;
	t_bool	single;

	quote = FALSE;
	len = 0;
	while (*str && !(*str == ' ' && !quote))
	{
		if (*str == '"' && !quote)
			single = FALSE;
		else if (*str == '\'' && !quote)
			single = TRUE;
		if ((*str == '"' && !single) || (*str == '\'' && single))
			quote = !quote;
		else
			len ++;
		str ++;
	}
	return (len);
}

char	*ft_quote_delimiter(char *str)
{
	char	*s;
	int		i;
	t_bool	quote;
	t_bool	single;

	s = ft_calloc(sizeof(char), ft_quote_len(str));
	i = 0;
	while (s && *str && !(*str == ' ' && !quote))
	{
		if (*str == '"' && !quote)
			single = FALSE;
		else if (*str == '\'' && !quote)
			single = TRUE;
		if ((*str == '"' && !single) || (*str == '\'' && single))
			quote = !quote;
		else
		{
			s[i] = *str;
			i ++;
		}
		str ++;
	}
	if (s)
		s[i] = 0;
	return (s);
}

void	ft_command_checker(t_data *data, char *command, char **adr)
{
	char	**path_ptr;
	char	*path;
	char	*name;

	path_ptr = data->cmd_path;
	name = ft_quote_delimiter(command);
	ft_printf("la -> %s\n", ft_quote_delimiter(command));
	while (*path_ptr)
	{
		path = ft_strjoin(*path_ptr, name);
		if (!path)
			data->error = TRUE;
		if (access(path, F_OK) || access(path, X_OK))
			free(path);
		else
		{
			*adr = path;
			return;
		}
		path_ptr ++;
	}
	if (!(access(name, F_OK) || access(name, X_OK)))
		*adr = path;
	else
	{
		perror(name);
		data->error = TRUE;
	}
}

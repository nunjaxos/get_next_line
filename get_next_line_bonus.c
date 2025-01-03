/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:23:39 by abhmidat          #+#    #+#             */
/*   Updated: 2024/12/24 20:23:40 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_until_nl(int fd, char *remainder)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(remainder, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(remainder);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin(remainder, buffer);
	}
	free(buffer);
	return (remainder);
}

char	*new_line(char *old_line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (old_line[i] && old_line[i] != '\n')
		i++;
	if (!old_line[i])
	{
		free(old_line);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * ft_strlen(old_line) - i);
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (old_line[i])
		str[j++] = old_line[i++];
	str[j] = '\0';
	free(old_line);
	return (str);
}

char	*extract_line(char **remainder)
{
	int		i;
	char	*str;

	if (!*remainder || !(*remainder)[0])
		return (NULL);
	i = 0;
	while ((*remainder)[i] && (*remainder)[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while ((*remainder)[i] && (*remainder)[i] != '\n')
	{
		str[i] = (*remainder)[i];
		i++;
	}
	if ((*remainder)[i] == '\n')
	{
		str[i] = (*remainder)[i];
		i++;
	}
	str[i] = '\0';
	*remainder = new_line(*remainder);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder[fd] = read_until_nl(fd, remainder[fd]);
	if (!remainder[fd] || *remainder[fd] == '\0')
	{
		if (remainder[fd])
		{
			free(remainder[fd]);
			remainder[fd] = NULL;
		}
		return (NULL);
	}
	line = extract_line(&remainder[fd]);
	return (line);
}

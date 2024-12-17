/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-16 11:05:07 by abhmidat          #+#    #+#             */
/*   Updated: 2024/12/16 12:37:43 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until_nl(int fd, char *remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*nl_pos;
	char	*tmp;
	
	if (!remainder)
		remainder = ft_strdup("");
	bytes_read = 1;

	while (!(nl_pos = ft_strchr(remainder, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(remainder);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(remainder, buffer);
		free(remainder);
		remainder = tmp;	
	}
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = read_until_nl(fd, remainder);
	if (!remainder || *remainder == '\0')
	{
		if (remainder)
		{
			free(remainder);
			remainder = NULL;
		}
		return (NULL);
	}
	return (extract_line(&remainder));
}




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-16 11:05:00 by abhmidat          #+#    #+#             */
/*   Updated: 2024/12/16 12:31:37 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != (char)c)
	{
		if (!s[i])
			return (0);
		i++;
	}
	return ((char *)s + i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*st_join;
	int		i;
	int		j;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && !s2)
		return (NULL);
	st_join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!st_join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		st_join[j++] = s1[i++];
	i = 0;
	while (s2[i])
		st_join[j++] = s2[i++];
	st_join[j] = '\0';

	free((void *)s1);
	return (st_join);
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
	str = (char *)malloc(sizeof(char) * ft_strlen(old_line) - i + 1);
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

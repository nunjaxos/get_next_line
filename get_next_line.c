#include "get_next_line.h"

char	*read_until_nl(int fd, char *remainder)
{
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;
    char *nl_pos;
    char *tmp;

    while (!(nl_pos = ft_strchr(remainder, '\n')) &&
           (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        tmp = ft_strjoin(remainder, buffer);
        if (remainder)
            free(remainder);
        remainder = tmp;
    }
    return (remainder);
}

char	*get_next_line(int fd)
{
    static char	*remainder;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    remainder = read_until_nl(fd, remainder);
    if (!remainder || *remainder == '\0')
    {
        if (remainder)
	{
            free(remainder);
            remainder = NULL;
        }
        return NULL;
    }

    return (extract_line(&remainder));
}

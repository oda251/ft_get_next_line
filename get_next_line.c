#include "get_next_line.h"

static char	*str_push_back(char *str, char c, size_t len)
{
	char	*dest;
	size_t	i;

	dest = malloc(len + 2);
	if (!dest)
		return (NULL);
	dest[len + 2] = '\0';
	i = 0
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = c;
	return (dest)
}

char	*get_next_line(int fd)
{
	char	*dest;
	char	*buf;
	size_t	len;

	dest = ft_calloc(1, 1);
	if (!dest)
		return (NULL);
	len = 0;
	while (read(fd, buf, 1) > 0)
	{
		if (*buf == '\n')
			break ;
		dest = str_push_back(dest, *buf, len);
		len++;
	}
}
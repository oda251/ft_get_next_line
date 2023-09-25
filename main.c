#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int c, char **v)
{
	int fd;
	char *line;

	if (c == 2)
	{
		fd = open(v[1], O_RDONLY);
		while ((line = get_next_line(fd)))
		{
			printf("%s\n", line);
			free(line);
		}
		close(fd);
	}
	return (0);
}
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fds[argc - 1];
	char	*line;
	int		active_files;

	int i, open_files = 0;
	if (argc < 2)
	{
		printf("Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
		return (1);
	}
	// Abre todos los archivos proporcionados por argumentos.
	for (i = 1; i < argc; i++)
	{
		fds[i - 1] = open(argv[i], O_RDONLY);
		if (fds[i - 1] == -1)
		{
			perror("Error opening file");
			continue ;
		}
		open_files++;
	}
	// Lee de cada archivo línea por línea y las imprime hasta que todos estén completos.
	active_files = open_files;
	while (active_files > 0)
	{
		for (i = 0; i < open_files; i++)
		{
			if (fds[i] != -1)
			{
				line = get_next_line(fds[i]);
				if (line == NULL)
				{
					close(fds[i]);
					fds[i] = -1;
					active_files--;
				}
				else
				{
					printf("File %d: %s", i + 1, line);
					free(line);
				}
			}
		}
	}
	return (0);
}

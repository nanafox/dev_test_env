#include "main.h"

/**
 * main - tests the custom getline function
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t n_read = 0;
	int retval = 0, running = 1;
	path_t *path_list = NULL;

	path_list = build_path(&path_list);

	while (running)
	{
		/*printf("mdsh$ ");*/
		fflush(stdout);

		n_read = _getline(&line, &len, STDIN_FILENO);
		if (n_read == -1)
		{
			safe_free(line);
			perror("_getline");
			return (-1);
		}

		if (n_read == 0)
		{
			/*printf("\n");*/
			safe_free(line);
			free_list(&path_list);
			/* most definitely Ctrl+D or Ctrl+C was received */
			return (retval);
		}
		if ((n_read == 1 && *line == '\n') || *line == '#')
			continue; /* skip normal ENTER keys and comments */

		retval = parse_line(line, path_list);
		safe_free(line);
	}
	free_list(&path_list);

	return (retval);
}

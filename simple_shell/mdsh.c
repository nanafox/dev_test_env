#include "main.h"

/**
 * main - the entry point for the shell
 * @argc: command line arguments counter
 * @argv: command line arguments
 *
 * Return: 0 on success, or the exit code of the just exited process
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t n_read = 0;
	int exit_code = 0, running = 1;
	path_t *path_list = NULL;

	path_list = build_path(&path_list);
	if (argc >= 2)
	{
		exit_code = handle_file_as_input(argv[1], path_list);
		free_list(&path_list);
		return (exit_code);
	}
	while (running)
	{
		printf("%s", (isatty(STDIN_FILENO)) ? "mdsh$ " : "");
		fflush(stdout);

		n_read = _getline(&line, &len, STDIN_FILENO);
		if (n_read == -1)
		{
			safe_free(line);
			perror("_getline");
			return (-1);
		}
		if (n_read == 0) /* most definitely Ctrl+D or Ctrl+C was received */
			break;

		exit_code = parse_line(line, path_list);
		safe_free(line);
	}
	safe_free(line);
	free_list(&path_list);

	return (exit_code);
}

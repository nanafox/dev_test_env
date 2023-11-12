#include "main.h"

/**
 * handle_variables - handles variables passed to the shell
 * @command: the command to process for variables
 * @exit_code: the exit code of the last process
 *
 * Return: the updated command with variables expanded if one was found, else
 * the @command is returned as received with no modifications
 */
char **handle_variables(char **command, int exit_code)
{
	size_t i;
	ssize_t offset;
	char *value, *loc, result[32];

	for (i = 0; command[i] != NULL; i++)
	{
		loc = _strchr(command[i], '$');
		if (loc == NULL)
			continue; /* no variables found yet? keep, searching till the end */

		offset = (&loc[0]) - (&command[i][0]);

		if (command[i][offset + 1] == '\0')
			continue; /* this is just a literal '$' sign, ignore it */

		/* what's my PID? that's what this guy tells you */
		if (command[i][offset + 1] == '$')
		{
			_itoa(getpid(), result);
			safe_free(command[i]);
			command[i] = _strdup(result);
		}
		/* this is for when the user wants the exit code of the last process */
		else if (command[i][offset + 1] == '?')
		{
			_itoa(exit_code, result);
			safe_free(command[i]);
			command[i] = _strdup(result);
		}
		/* this is for when something like '$HOSTNAME' is received */
		else
		{
			value = _getenv(loc + 1);
			safe_free(command[i]);
			command[i] = _strdup(value);
		}
	}

	return (command);
}

/**
 * handle_file_as_input - handles execution when a file is given as input on
 * the command line (non-interactive mode)
 * @filename: the name of file containing the commands
 * @path_list: a list of pathnames in the PATH variable
 *
 * Return: 0, or the exit status of the just exited process
 */
int handle_file_as_input(char *filename, path_t *path_list)
{
	char *line = NULL;
	size_t n = 0;
	int n_read, fd, exit_code = 0;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		dprintf(2, "%s: 0: Can't open %s\n", _getenv("_"), filename);
		return (CMD_NOT_FOUND);
	}

	n_read = _getline(&line, &n, fd);
	close(fd);

	if (n_read == -1)
	{
		return (-1); /* reading file failed */
	}

	if (n_read)
		exit_code = parse_line(line, path_list);

	_free_on_exit("sp", line, &path_list);

	return (exit_code);
}

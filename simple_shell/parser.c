#include "main.h"

/**
 * parse_line - parses the receive command line, processes it before handing it
 * over to the executor only after it has confirmed the command is valid
 * @line: the command line received
 * @path_list: a list of pathnames in the PATH variable
 *
 * Return: the exit code of the executed program, else -1 if something goes
 * wrong
 */
int parse_line(char *line, path_t *path_list)
{
	char **commands = NULL;

	/* first of all, let's get rid of all comments */
	line = handle_comments(line);

	/* now let's all the commands provided by the user */
	commands = _strtok(line, "\n;");
	if (commands == NULL)
	{
		perror("_strtok");
		return (-1); /* an error occurred while getting the commands */
	}

	return (parse_and_execute(commands, path_list));
}

/**
 * parse_and_execute - parses each sub command line and executes it
 * @commands: an array of command line strings
 * @path_list: a list of pathnames in the PATH variable
 *
 * Return: the exit code of the executed program, else -1 if something goes
 * wrong
 */
int parse_and_execute(char **commands, path_t *path_list)
{
	ssize_t retval = 0;
	size_t i;
	char **sub_command = NULL;

	for (i = 0; commands[i] != NULL; i++)
	{
		/* get the sub commands and work on them */
		sub_command = _strtok(commands[i], NULL);

		if (sub_command == NULL)
		{
			free_str(commands);
			return (0); /* probably just lots of tabs or spaces, maybe both */
		}

		if (path_list != NULL)
		{
			/* handle the command with the PATH variable */
			retval = handle_with_path(path_list, sub_command);
			if (retval == -1)
				retval = print_cmd_not_found(sub_command, commands, i);
		}
		else
		{
			struct stat st;

			if (sub_command && stat(sub_command[0], &st) == 0)
				retval = execute_command(sub_command[0], sub_command);
			else
				retval = print_cmd_not_found(sub_command, commands, i);
		}
		safe_free(commands[i]);
		free_str(sub_command);
	}

	free_str(commands);
	return (retval);
}

/**
 * handle_with_path - handles commands when the PATH is set
 * @path_list: a list of pathnames in the PATH variable
 * @sub_command: the command to execute
 *
 * Return: the exit code of the child process, else -1 if the command is not in
 * the PATH provided
 */
int handle_with_path(path_t *path_list, char **sub_command)
{
	char path[50];
	struct stat st;

	while (path_list != NULL && sub_command != NULL)
	{
		sprintf(path, "%s%s%s", path_list->pathname, "/", sub_command[0]);
		if (stat(path, &st) == 0)
		{
			return (execute_command(path, sub_command));
		}
		else if (stat(sub_command[0], &st) == 0)
		{
			return (execute_command(sub_command[0], sub_command));
		}
		path_list = path_list->next;
	}

	return (-1);
}

/**
 * print_cmd_not_found - prints the command not found error
 * @sub_command: the actual command executed
 * @commands: a list of commands received on the command line
 * @index: current index in the commands list
 *
 * Return: 127 command not found code, else 0
 */
int print_cmd_not_found(char **sub_command, char **commands, size_t index)
{
	static size_t err_count = 1;

	dprintf(STDERR_FILENO, "./hsh: %lu: %s: not found\n",
			err_count, sub_command[0]);
	err_count++;

	if (commands[index + 1] == NULL)
	{
		return (CMD_NOT_FOUND); /* command not found */
	}

	return (0);
}

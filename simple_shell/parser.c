#include "main.h"

static int exit_code; /* keeps track of all exit codes */
static alias_t *aliases;
int handle_logical_operators(char **commands, path_t *path_list, char *line);
char *get_operator(char *str);

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

	/* skip normal ENTER keys and leading comments */
	if (*line == '\n' || *line == '#')
		return (0);

	/* first of all, let's get rid of all comments */
	line = handle_comments(line);

	/* now let's all the commands provided by the user */
	commands = _strtok(line, "\n;");
	if (commands == NULL)
	{
		perror("_strtok");
		return (-1); /* an error occurred while getting the commands */
	}

	return (handle_logical_operators(commands, path_list, line));
}

/**
 * parse_and_execute - parses each sub command line and executes it
 * @commands: an array of command line strings
 * @path_list: a list of pathnames in the PATH variable
 * @line: the command line received
 *
 * Return: the exit code of the executed program, else -1 if something goes
 * wrong
 */
int parse_and_execute(char **commands, path_t *path_list, char *line)
{
	size_t i;
	char **sub_command = NULL;

	printf("I am running... no logicals\n");
	for (i = 0; commands[i] != NULL; i++)
	{
		/* get the sub commands and work on them */
		sub_command = _strtok(commands[i], NULL);
		if (sub_command == NULL)
		{
			free_str(commands);
			return (0); /* probably just lots of tabs or spaces, maybe both */
		}

		sub_command = handle_variables(sub_command, exit_code);
		parse_helper(commands, sub_command, path_list, line, i);
	}

	return (exit_code);
}

/**
 * parse_helper - performs extra parsing on behalf of the parse and execute
 * function
 * @commands: an array of commands receieved on the command line
 * @sub_command: an array of sub commands generated from the commands array
 * @path_list: a list of PATH directories
 * @line: the actual line the user typed on the prompt
 * @index: the current index in sub_commands array
 */
void parse_helper(char **commands, char **sub_command,
		path_t *path_list, char *line, size_t index)
{
	char *alias_value;

	if (!_strcmp(sub_command[0], "alias") || !_strcmp(sub_command[0], "unalias"))
	{
		exit_code = handle_alias(&aliases, sub_command);
		free_str(sub_command);
		return;
	}

	alias_value = get_alias(aliases, sub_command[0]);
	if (alias_value != NULL)
	{
		safe_free(sub_command[0]);
		sub_command[0] = _strdup(alias_value);
		safe_free(alias_value);
	}
	exit_code = handle_builtin(sub_command, commands, line, aliases, path_list,
			exit_code);
	if (exit_code != NOT_BUILTIN)
	{
		free_str(sub_command);
		return; /* shell builtin executed well */
	}

	if (path_list != NULL) /* handle the command with the PATH variable */
	{
		exit_code = handle_with_path(path_list, sub_command);
		if (exit_code == -1)
			exit_code = print_cmd_not_found(sub_command, commands, index);
		free_str(sub_command);
	}
	else
	{
		if (access(sub_command[0], X_OK) == 0 && _strchr(sub_command[0], '/'))
			exit_code = execute_command(sub_command[0], sub_command);
		else
			exit_code = print_cmd_not_found(sub_command, commands, index);
		free_str(sub_command);
	}
}

/**
 * handle_logical_operators - handles logical operators in a command line
 * @commands: an array of command line strings
 * @path_list: a list of pathnames in the PATH variable
 * @line: the command line received
 *
 * Return: the exit code of the executed program
 */
int handle_logical_operators(char **commands, path_t *path_list, char *line)
{
	ssize_t i, offset;
	char **sub_command = NULL, *cmd = NULL, *operator = NULL, *next_cmd = NULL;

	for (i = 0; commands[i] != NULL; i++)
	{
		operator = get_operator(commands[i]);

		if (operator != NULL)
		{
			offset = strcspn(commands[i], operator);
			/* Extract the command before the operator */
			cmd = strndup(commands[i], offset);
			if (cmd == NULL)
				return (0);

			/* Tokenize the command */
			sub_command = _strtok(cmd, NULL);
			safe_free(cmd);

			if (sub_command == NULL)
			{
				free_str(commands);
				return (0);
			}

			/* Handle variables and execute the command */
			sub_command = handle_variables(sub_command, exit_code);
			parse_helper(commands, sub_command, path_list, line, i);
			
			next_cmd = &commands[i][offset + 2];
			/* Check the exit code and continue accordingly */
			if ((!_strcmp(operator, "&&") && exit_code == 0) ||
					(!_strcmp(operator, "||") && exit_code != 0))
			{
				commands[i] = next_cmd;
				handle_logical_operators(commands, path_list, line);
			}
		}
		else
		{
			/* If no operator is found, tokenize and handle the command */
			sub_command = _strtok(commands[i], NULL);
			if (sub_command == NULL)
			{
				free_str(commands);
				return (0);
			}

			sub_command = handle_variables(sub_command, exit_code);
			parse_helper(commands, sub_command, path_list, line, i);
		}
	}

	return (exit_code);
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

	dprintf(STDERR_FILENO, "%s: %lu: %s: not found\n",
			_getenv("_"), err_count, sub_command[0]);
	err_count++;

	if (commands[index + 1] == NULL)
	{
		return (CMD_NOT_FOUND); /* command not found */
	}

	return (0);
}

/**
 * get_operator - returns the && or || logical operator in a string if found
 * @str: the string to search
 *
 * Return: && or || if found, else NULL
 */
char *get_operator(char *str)
{
	char *operator = NULL;
	int i;

	if (str == NULL)
		return (NULL);

	/* Check for "||" operator */
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '&' && str[i + 1] == '&')
		{
			operator = "&&";
			break;
		}
		else if (str[i] == '|' && str[i + 1] == '|')
		{
			operator = "||";
			break;
		}
	}


	return (operator);
}

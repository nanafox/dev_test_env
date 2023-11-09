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
 * handle_exit - handles the built-in `exit` command for the shell
 * @exit_code: the user provided exit code
 * @status: the exit status of the last executed process (used if the exit code
 * is not provided)
 * @cleanup: a pointer to the function that handles memory deallocation on exit
 * @commands: an array of command line strings
 * @sub_command: the command to execute
 * @path_list: a list of pathnames in the PATH variable
 * @line: the command line received
 *
 * Return: 2 on error, else exits with @exit_code
 */
int handle_exit(char *exit_code, int status,
		void (*cleanup)(const char *format, ...),
		char **sub_command, char **commands, path_t **path_list, char *line)
{
	size_t illegal_num_count = 1;
	int code;

	if (exit_code == NULL)
	{
		cleanup("ttps", sub_command, commands, path_list, line);
		exit(status);
	}

	if (isalpha(*exit_code) || _atoi(exit_code) < 0 || *exit_code == '-')
	{
		dprintf(STDERR_FILENO, "./hsh: %lu: exit: Illegal number: %s\n",
				illegal_num_count, exit_code);
		illegal_num_count++;
		return (CMD_ERR);
	}

	code = _atoi(exit_code);
	cleanup("ttps", sub_command, commands, path_list, line);
	exit(code);
}

/**
 * _free_on_exit - frees dynamically allocated memory when the exit command is
 * issued on the command line
 * @format: the format of how dynamically allocated variables are given
 *
 * Description: 's' is for a normal string (char *)
 *				't' is for an array of strings (char **)
 *				'p' is for the path_t list
 */
void _free_on_exit(const char *format, ...)
{
	va_list ap;
	char *line;

	va_start(ap, format);

	while (*format != '\0')
	{
		switch (*format)
		{
			case 's':
				line = va_arg(ap, char *);
				safe_free(line);
				break;
			case 't':
				free_str(va_arg(ap, char **));
				break;
			case 'p':
				free_list(va_arg(ap, path_t **));
				break;
			default:
				break;
		}
		format++;
	}
}

/**
 * handle_cd - handles the builtin `cd` command
 * @pathname: the string containing the path to change directory to
 *
 * Return: 0 on success, else 2 on error
 */
int handle_cd(const char *pathname)
{
	char *home = _getenv("HOME");
	char *oldpath = _getenv("OLDPWD");
	char pwd[BUFF_SIZE];
	static size_t cd_err_count = 1;

	getcwd(pwd, BUFF_SIZE);
	oldpath = (oldpath) ? oldpath : pwd;
	if (pathname != NULL)
	{
		int dash = !_strcmp(pathname, "-") || !_strcmp(pathname, "--");
		char path[PATH_SIZE];

		/* build the full path when relative paths are given */
		if (!_strchr(pathname, '/') && !dash)
			sprintf(path, "%s/%s", pwd, ((dash) ? oldpath : pathname));
		else
			sprintf(path, "%s", ((dash) ? oldpath : pathname));
		if (chdir(path) == -1)
		{
			if (strspn(pathname, "-") > 2)
				dprintf(2, "./hsh: %lu: cd: Illegal option: --\n", cd_err_count);
			else
				dprintf(2, "./hsh: %lu: cd: can't cd to %s\n", cd_err_count, pathname);
			cd_err_count++;
			return (CMD_ERR);
		}
		if (dash)
			printf("%s\n", oldpath);
		setenv("OLDPWD", pwd, 1);
		getcwd(path, PATH_SIZE);
		setenv("PWD", path, 1);
	}
	else
	{
		if (chdir(home) == -1)
			return (CMD_ERR);
		setenv("OLDPWD", pwd, 1);
		setenv("PWD", home, 1);
	}
	return (0);
}

#include "main.h"

/**
 * main - tests the custom getline function
 * Return: 0
 */
int main(void)
{
	char **args = NULL, *line = NULL;
	size_t len = 0;
	ssize_t n_read = 0;
	int status, retval, running = 1;
	pid_t pid;

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
			/* most definitely Ctrl+D or Ctrl+C was received */
			return (0);
		}
		if ((n_read == 1 && *line == '\0') || *line == '#')
			continue; /* skip normal ENTER keys and comments */

		pid = fork();
		if (pid == -1)
		{
			safe_free(line);
			perror("fork");
			return (-1);
		}
		if (!pid && n_read > 0)
		{
			/* line = parse_line(line) */
			line = handle_comments(line);
			args = _strtok(line, NULL);
			if (args)
			{
				retval = execve(args[0], args, environ);
				safe_free(line);
				free_str(args);
				if (retval == -1)
				{
					perror("execve");
					fflush(stdout);
					break; /* get out the failed process */
				}
			}
			else
			{
				safe_free(line);
				break;
			}
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1) /* wait for the child process */
				perror("wait");
		}
	}

	return (0);
}

#include "main.h"

/**
 * main - tests the custom getline function
 * @argc: counter
 * @argv: vector
 * @env: env
 * Return: 0
 */
int main(__attribute__((unused)) int argc,
		 __attribute__((unused)) char *argv[], char *env[])
{
	char **words, *line = NULL;
	size_t len = 0;
	ssize_t n_read = 0;
	int status, retval, active_state = RUNNING;
	pid_t pid;

	while (active_state == RUNNING)
	{
		char path[30] = "/bin/";

		printf("mdsh$ ");
		fflush(stdout);

		n_read = _getline(&line, &len, STDIN_FILENO);
		if (n_read == -1)
		{
			perror("_getline");
			return (-1);
		}

		if (n_read == 0)
		{
			printf("\n");
			safe_free(line);
			/* most definitely Ctrl+D or Ctrl+C was received */
			active_state = 0;
		}
		if (n_read == 1 && *line == '\0')
			continue; /* skip normal ENTER keys */

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		if (!pid && n_read > 0)
		{
			words = _strtok(line, NULL);
			_strcat(path, words[0]);
			retval = execve(path, &words[0], env);
			if (retval == -1)
			{
				perror("execve");
				continue;
			}
			safe_free(words);
		}
		else
			wait(&status); /* wait for the child process */

		safe_free(line);
		len = 0;
	}
	safe_free(line);

	return (0);
}

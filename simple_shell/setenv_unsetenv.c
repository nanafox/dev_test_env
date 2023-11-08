#include "main.h"

/**
 * _setenv - Set a custom environment variable
 * @name: The name of the variable
 * @value: The value to set
 * @overwrite: If true, overwrite the variable if it exists
 *
 * This function sets a custom environment variable with the given name and
 * value. If the variable already exists and overwrite is true, it will be
 * replaced.
 *
 * Return: 0 on success, -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	size_t len;
	char *env_var;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
	{
		fprintf(stderr, "Invalid variable name: %s\n", name);
		return -1;
	}

	/* check if the variable already exists */
	if (_getenv(name) != NULL)
	{
		if (overwrite)
		{
			if (unsetenv(name) != 0)
			{
				perror("_setenv");
				return (-1);
			}
		}
		else
		{
			return (0); /* variable exists, and overwrite is false */
		}
	}

	/* allocate memory for the new environment variable */
	len = _strlen(name) + _strlen(value) + 2; /* 1 for '=' and 1 for '\0' */
	env_var = malloc(len);
	if (env_var == NULL)
		return (-1);

	/* create the environment variable in the format "name=value" */
	snprintf(env_var, len, "%s=%s", name, value);

	/* add the environment variable */
	if (putenv(env_var) != 0)
	{
		free(env_var);
		return (-1);
	}

	free(env_var);
	return (0);
}

/**
 * _unsetenv - unset a custom environment variable
 * @name: The name of the variable to unset
 *
 * Description: This function unsets a custom environment variable with the
 * given name.
 *
 * Return: 0 on success, -1 on error
 */
int _unsetenv(const char *name)
{
	size_t i, j, len;

	/* check for invalid variable names */
	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
	{
		fprintf(stderr, "Invalid variable name: %s\n", name);
		return (-1);
	}

	len = _strlen(name);

	/* iterate through the environment variables and find the one to remove */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			/* shift all environment variables after the one to be removed */
			for (j = i; environ[j] != NULL; j++)
			{
				environ[j] = environ[j + 1];
			}
			return (0);
		}
	}

	dprintf(STDERR_FILENO, "Variable not found: %s\n", name);
	return (-1);
}

#include "main.h"

/**
 * _getenv - get an environment variable
 * @name: the name of the environment variable to look for
 *
 * Return: a pointer to the value in the environment,
 * or NULL if there is no match
 */
char *_getenv(const char *name)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		/* check if we found a match */
		if (_strstr(environ[i], name))
		{
			/* move past the equal to sign and return the actual value */
			return ((_strchr(environ[i], '=')) + 1);
		}
	}

	return (NULL);
}

/**
 * _printenv - prints all environment variables
 */
void _printenv(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * build_path - builds a list of paths in the PATH environment variable
 * @head: a pointer to the head node
 *
 * Return: a pointer to the head onn success, else NULL on failure.
 */
path_t *build_path(path_t **head)
{
	size_t i = 0;
	char *path_value = _getenv("PATH");
	char **pathnames = _strtok(path_value, ":");
	path_t *new_node, *tail;

	while (pathnames[i] != NULL)
	{
		new_node = malloc(sizeof(path_t));
		if (new_node == NULL)
		{
			return (NULL);
		}

		new_node->pathname = _strdup(pathnames[i]);
		_strcpy(new_node->pathname, pathnames[i]);
		new_node->next = NULL;

		if (*head == NULL)
		{
			*head = new_node;
		}
		else
		{
			tail = *head;
			while (tail->next != NULL)
			{
				tail = tail->next;
			}
			tail->next = new_node;
		}
		safe_free(pathnames[i]);
		i++;
	}

	free_str(pathnames);

	return (*head);
}

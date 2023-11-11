#include "main.h"

/**
 * free_list - frees a path_t list
 * @head: the head node
 */
void free_list(path_t **head)
{
	path_t *current_node;

	while (*head != NULL)
	{
		current_node = *head;
		*head = (*head)->next; /* move to the next node */
		safe_free(current_node->pathname); /* free memory allocated for the string */
		safe_free(current_node); /* free memory for the current node */
	}
}

/**
 * free_aliases - frees an alias_t list
 * @head: a pointer to the list containing the aliases
 */
void free_aliases(alias_t **head)
{
	alias_t *current;

	while (*head != NULL)
	{
		current = *head;
		*head = (*head)->next;

		/* free memory */
		safe_free(current->name);
		safe_free(current->value);
		safe_free(current);
	}
}
/**
 * _free_on_exit - frees dynamically allocated memory when the exit command is
 * issued on the command line
 * @format: the format of how dynamically allocated variables are given
 *
 * Description: 's' is for a normal string (char *)
 *				't' is for an array of strings (char **)
 *				'p' is for the path_t list
 *				'a' is for the alias_t list
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
			case 'a':
				free_aliases(va_arg(ap, alias_t **));
				break;
			default:
				break;
		}
		format++;
	}
}

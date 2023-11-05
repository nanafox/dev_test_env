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

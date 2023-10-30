#include "node.h"

size_t list_len(Node *head)
{
	size_t node_count = 0;

	if (head == NULL)
	{
		return (0);
	}

	while (head != NULL)
	{
		head = head->next;
		node_count++;
	}

	return (node_count);
}

size_t print_list(Node *head)
{
	size_t node_count = 0;

	if (head == NULL)
	{
		printf("List is empty\n");
		return (0);
	}

	while (head != NULL)
	{
		printf("[%p] -> %3d\n", (void *)head, head->data);
		head = head->next;
		node_count++;
	}

	return (node_count);
}

void free_list(Node **head)
{
	Node *tmp_head;

	if (*head == NULL)
	{
		printf("List is empty, there's nothing to do!\n");
		return;
	}

	while (*head != NULL)
	{
		tmp_head = *head;
		*head = (*head)->next;
		safe_free(tmp_head);
	}
}

/**
 * _free - a safer way to free dynamically allocated memory
 * @ptr: pointer to memory location
 *
 * Description: This _free() function takes care of freeing
 * dynamically allocated memory while ensuring the pointer
 * @ptr passed to it is not NULL before trying to free it.
 * Also, after freeing the memory, it sets the pointer @ptr
 * to NULL to avoid the issue of dangling pointers.
 */
void _free(void **ptr)
{
	if (ptr != NULL || *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/**
 * compare - returns 1 if x is less than y, else 0 otherwise
 * @x: value for x
 * @y: value for y
 *
 * Return: 1 if x less than y, 0 otherwise
 */
int compare(int x, int y)
{
	return (x < y);
}

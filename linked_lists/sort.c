#include "node.h"

/**
 * sort - sort a linked list (uses the selection sort algorithm)
 * @head: pointer to the head node
 * @compare: a function pointer to compare data value for swapping
 *
 * Return: a pointer to the head (now sorted list), or NULL if list is empty
 */
Node *sort(Node **head, int (*compare)(int x, int y))
{
	Node *x, *y;
	int tmp;
	
	if (head == NULL || *head == NULL)
	{
		return (NULL); /* list is empty */
	}

	x = *head;

	while (x != NULL)
	{
		y = x->next;

		while (y != NULL)
		{
			if (compare(y->data, x->data) > 0)
			{
				tmp = x->data;
				x->data = y->data;
				y->data = tmp;
			}
			y = y->next;
		}
		x = x->next;
	}

	return (*head);
}

#include "node.h"

/**
 * creates_node - creates a new node for multiple usages
 *
 * Return: the address of the new node on success,
 * else prints an error message and exits with code 1
 */
Node *create_node(void)
{
	Node *new_node = malloc(sizeof(Node));

	if (new_node == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	return (new_node); /* return the newly created node */
}

/**
 * add_node - adds a node to the beginning of a list
 * @head: a pointer to the starting point of the list
 * @data: the integer value to store
 *
 * Return: the address of the newly added node
 */
Node *add_node(Node **head, int data)
{
	Node *new_node = create_node();

	new_node->data = data;
	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

/**
 * add_node_at_index - inserts a node to a particular index in a list
 * @head: a pointer to the starting point of the list
 * @data: the integer value to store
 * @index: the index position to insert at (starts from 0)
 *
 * Return: the address of the newly added node, or NULL if node couldn't
 * be inserted.
 */
Node *add_node_at_index(Node **head, int data, int index)
{
	int i = 0;
	Node *new_node, *tmp_head;

	/* check if the list is empty */
	if (*head == NULL)
	{
		return (add_node(head, data));
	}

	new_node = create_node();
	new_node->data = data;
	new_node->next = NULL;
	tmp_head = *head;

	while (tmp_head != NULL)
	{
		if (i == (index - 1))
		{
			new_node->next = tmp_head->next;
			tmp_head->next = new_node;
			return (new_node);
		}
		i++;
		tmp_head = tmp_head->next;
	}

	safe_free(new_node);
	return (NULL);
}

/**
 * append_node - appends a node to the end of a list
 * @head: a pointer to the starting point of the list
 * @data: the integer value to store
 *
 * Return: the address of the newly added node
 */
Node *append_node(Node **head, int data)
{
	Node *new_node, *tail;

	if (*head == NULL)
	{
		return (add_node(head, data));
	}

	new_node = create_node();
	new_node->data = data;
	new_node->next = NULL;

	tail = *head;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = new_node;

	return (new_node);
}

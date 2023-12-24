#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * struct Node - a blueprint for a node
 * @data: the integer value to store
 * @next: a pointer to the next node
 */
typedef struct Node
{
	int data;
	struct Node *next;
} Node;

/* already written functions */

Node *create_node(void);
Node *add_node(Node **head, int data);
Node *add_node_at_index(Node **head, int data, int index);
Node *append_node(Node **head, int data);

size_t print_list(Node *head);
size_t list_len(Node *head);
int compare(int x, int y);

void free_list(Node **head);
void _free(void **ptr);
#define safe_free(p) _free((void **) &(p))

/* functions for you to write */

/* this sort function must use the 'compare()' function */
Node *sort(Node **head, int (*compare)(int x, int y));

/* you will have to use to linked lists you have sorted to complete it */
Node *merge(Node *list_1, Node *list2);


#endif /* NODE_H */

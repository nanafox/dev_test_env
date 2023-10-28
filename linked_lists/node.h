#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

/* function prototypes */
Node *create_node(void);
Node *add_node(Node **head, int data);
Node *add_node_at_index(Node **head, int data, int index);
Node *append_node(Node **head, int data);
Node *sort(Node **head, int (*compare)(int x, int y));
Node *merge(Node *list_1, Node *list2);
size_t print_list(Node *head);
size_t list_len(Node *head);
void free_list(Node **head);
void _free(void **ptr);
#define safe_free(p) _free((void **) &(p))

#endif /* NODE_H */

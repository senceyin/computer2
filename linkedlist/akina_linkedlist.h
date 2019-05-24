#include <stdio.h>
#include <stdlib.h>


#ifndef LINKEDLIST
#define LINKEDLIST

struct linkedlist {
    int size;
    struct node *head;
    struct node *tail;
};
typedef struct linkedlist ll_t;

struct node {
    int val;
    struct node* next;
};
typedef struct node node_t;

/*
list_init
Creates a new list by creating and head node
:: int value :: The value to be stored in the head node
Returns a pointer to the newly created node
*/
struct linkedlist *list_init();
/*
list_add
Adds a node containing a specified value to an existing list
:: int value :: The value to be stored in the new node
Does not return anything
*/
void list_add(struct linkedlist* lst, int value);

/*

list_delete
Removes the specified node from the list and updates the list accord
:: struct node* n :: The pointer to the node to be deleted
Does not return anything
*/
void list_delete(struct linkedlist* lst, int target);

/*
list_free
Frees all existing nodes in a list
:: struct node* n :: The pointer to the head node of the list
Does not return anything
*/
void list_free(struct linkedlist* lst);


node_t* list_get_at_index(struct linkedlist* lst, int i);


void print_linkedlist(struct linkedlist* lst);

#endif /* LINKEDLIST */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "akina_linkedlist.h"


#define NEW(T)     (T *)malloc(sizeof(T))
// #define NEW(T, n)  (T *)malloc(sizeof(T)*n)


node_t* create_node(int value){
    // node_t* new_node = malloc(sizeof(node_t));
    node_t* new_node = NEW(node_t);
    new_node->val = value;
    new_node->next = NULL;
    return new_node;
}

ll_t *list_init(){
    // ll_t* lst = malloc(sizeof(ll_t));
    ll_t* lst = NEW(ll_t);
    node_t* dummynode =  create_node(0xCAFEBABE);
    lst->head = dummynode;
    lst->tail = dummynode;
    lst->size = 0;
    return lst;
}

// without dummynode
// void list_add(ll_t* lst, int value){
//     node_t* new_node = create_node(value);
//     if(lst->tail==NULL){
//         lst->head = new_node;
//         lst->tail = new_node;
//     } else {
//         lst->tail->next = new_node;
//         lst->tail = new_node;
//     }
//     lst->size+=1;
// }

void list_add(ll_t* lst, int value){
    node_t* new_node = create_node(value);
    lst->tail->next = new_node;
    lst->tail = new_node;
    lst->size++;
}


void list_delete(struct linkedlist* lst, int target)
{
    //general -> special
    node_t* cur = lst->head;
    while(cur->next != NULL && cur->next->val != target){
        cur = cur->next;
    }
    if(cur->next!=NULL){
        node_t* temp = cur->next;
        cur->next = temp->next;
        free(temp);
        lst->size--;
    }
}

void list_free(struct linkedlist* lst){
    node_t* cur = lst->head;
    while(cur!=NULL){
        node_t* temp = cur;;
        cur = cur->next;
        free(temp);
    }
    free(lst);
}

void print_linkedlist(ll_t* lst){
    node_t* cur = lst->head->next;
    while(cur!=NULL){
        printf("[%d]->", cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
}


node_t* list_get_at_index(struct linkedlist* lst, int i){
    if(i < lst->size){
        node_t* cur = lst->head->next;
        while(i>0){
            cur = cur->next;
            i--;
        }
        return cur;
    }else{
        return NULL;
    }
}

int main(int argc, char* argv[])
{
    ll_t* lst = list_init();
    for (size_t i = 0; i < 10; i++)
    {
        list_add(lst, i*10);
    }
    print_linkedlist(lst);
    node_t *res = list_get_at_index(lst, 10);
    if (res != NULL)
    {
        printf("node at index==10 is [%d]\n", res->val);
    }
    else
    {
        printf("node at index==10 doesn't exisit\n");
    }
    list_delete(lst, 3);
    print_linkedlist(lst);
    list_delete(lst, 0);
    print_linkedlist(lst);
    list_delete(lst, 9);
    print_linkedlist(lst);
    list_delete(lst, 99);
    print_linkedlist(lst);
    free(lst);
    
    return 0;
}

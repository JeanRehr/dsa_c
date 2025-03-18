#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

/*
struct Node {
    int data;
    Node *next;
};

struct LList
{
    int size;
    Node *head;
};
*/

void init(LList *list)
{
    if (list != NULL) {
        list->head = NULL;
        list->size = 0;
    }
}

void free_list(LList *list)
{
    Node *current = list->head;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->size = 0;
    list->head = NULL;
}

Node* create_node(int data)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void prepend(LList *list, int data)
{
    Node *new_node = create_node(data);

    new_node->next = list->head;
    list->head = new_node;
    list->size += 1;
}

void append(LList *list, int data)
{
    if (list->size == 0) {
        prepend(list, data);
        return;
    }

    Node *new_node = create_node(data);
    Node *current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
    list->size += 1;
}

void insert_at(LList *list, int data, int pos)
{
    if (list->size == 0 || pos <= 0) {
        prepend(list, data);
        return;
    }

    if (pos >= list->size) {
        append(list, data);
        return;
    }

    Node *current = list->head;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }

    Node *new_node = create_node(data);
    Node *tmp = current->next;
    current->next = new_node;
    new_node->next = tmp;
    list->size += 1;
}

void delete_head(LList *list)
{
    if (list->size == 0) {
        return;
    }

    Node *tmp = list->head;
    list->head = list->head->next;

    free(tmp);
    list->size -= 1;
}

void delete_tail(LList *list)
{
    if (list->size == 0) {
        return;
    }

    if (list->size == 1) {
        delete_head(list);
        list->size = 0;
        return;
    }

    Node *second_last = list->head;

    for (int i = 0; i < list->size - 2; i++) {
        second_last = second_last->next;
    }

    /* example to delete tail
    0->1->2->3->4->null | size = 5
    go to 3 by going to the size - 2 (3)
    store a tmp pointer to the node at size - 2 (tail)
    assign it to null and free the tmp
    */

    Node *tmp = second_last->next;
    second_last->next = NULL;
    free(tmp);
    list->size -= 1;
}

void delete_value(LList *list, int data)
{
    Node *current = list->head;

    if (list->size == 0) {
        return;
    }

    if (current->data == data) {
        delete_head(list);
        return;
    }

    Node *previous = NULL;
    while (current != NULL && current->data != data) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    /* example to delete 2
    0->1->2->3->4->null | size = 5
    iterate until value is found
    now previous = 1 and current = 2
    link previous->next to current->next
    free current
    */

    previous->next = current->next;
    free(current);
    list->size -= 1;
}

void delete_at(LList *list, int pos)
{
    if (list->size == 0) {
        return;
    }

    if (pos <= 0) {
        delete_head(list);
        return;
    }

    if (pos >= list->size) {
        delete_tail(list);
        return;
    }

    /* example to delete 2
    0->1->2->3->4->null | size = 5
    iterate until pos given (pos = 2)
    current = 2, store a tmp pointer to current->next (3)
    link current->next (4) to tmp->next (3)
    0->1->3->4->null
    free tmp
    */

    Node *current = list->head;
    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
    }

    Node *tmp = current->next;
    current->next = tmp->next;
    free(tmp);
    list->size -= 1;
}

void print_list(LList *list)
{
    Node *current = list->head;

    while (current != NULL) {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("null\nSize = %d\n", list->size);
}
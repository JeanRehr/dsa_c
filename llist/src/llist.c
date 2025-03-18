#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

void llist_init(LList *list)
{
    if (list != NULL) {
        list->head = NULL;
        list->size = 0;
    }
}

void llist_deinit(LList *list)
{
    LLNode *current = list->head;
    LLNode *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->size = 0;
    list->head = NULL;
}

LLNode* llist_create_node(int data)
{
    LLNode *new_node = (LLNode*)malloc(sizeof(LLNode));
    
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void llist_prepend(LList *list, int data)
{
    LLNode *new_node = llist_create_node(data);

    new_node->next = list->head;
    list->head = new_node;
    list->size += 1;
}

void llist_append(LList *list, int data)
{
    if (list->size == 0) {
        llist_prepend(list, data);
        return;
    }

    LLNode *new_node = llist_create_node(data);
    LLNode *current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
    list->size += 1;
}

void llist_insert_at(LList *list, int data, int pos)
{
    if (list->size == 0 || pos <= 0) {
        llist_prepend(list, data);
        return;
    }

    if (pos >= list->size) {
        llist_append(list, data);
        return;
    }

    LLNode *current = list->head;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }

    LLNode *new_node = llist_create_node(data);
    LLNode *tmp = current->next;
    current->next = new_node;
    new_node->next = tmp;
    list->size += 1;
}

void llist_delete_head(LList *list)
{
    if (list->size == 0) {
        return;
    }

    LLNode *tmp = list->head;
    list->head = list->head->next;

    free(tmp);
    list->size -= 1;
}

void llist_delete_tail(LList *list)
{
    if (list->size == 0) {
        return;
    }

    if (list->size == 1) {
        llist_delete_head(list);
        list->size = 0;
        return;
    }

    LLNode *second_last = list->head;

    for (int i = 0; i < list->size - 2; i++) {
        second_last = second_last->next;
    }

    /* example to delete tail
    0->1->2->3->4->null | size = 5
    go to 3 by going to the size - 2 (3)
    store a tmp pointer to the node at size - 2 (tail)
    assign it to null and free the tmp
    */

    LLNode *tmp = second_last->next;
    second_last->next = NULL;
    free(tmp);
    list->size -= 1;
}

void llist_delete_value(LList *list, int data)
{
    LLNode *current = list->head;

    if (list->size == 0) {
        return;
    }

    if (current->data == data) {
        llist_delete_head(list);
        return;
    }

    LLNode *previous = NULL;
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

void llist_delete_at(LList *list, int pos)
{
    if (list->size == 0) {
        return;
    }

    if (pos <= 0) {
        llist_delete_head(list);
        return;
    }

    if (pos >= list->size) {
        llist_delete_tail(list);
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

    LLNode *current = list->head;
    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
    }

    LLNode *tmp = current->next;
    current->next = tmp->next;
    free(tmp);
    list->size -= 1;
}

void llist_print(const LList *list)
{
    LLNode *current = list->head;

    while (current != NULL) {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("null\nSize = %d\n", list->size);
}
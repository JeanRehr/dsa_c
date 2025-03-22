#ifndef LLIST_H
#define LLIST_H

typedef struct LLNode {
    int data;
    struct LLNode *next;
} LLNode;

typedef struct LList {
    int size;
    LLNode *head;
} LList;

void llist_init(LList *list);

void llist_deinit(LList *list);

void llist_prepend(LList *list, int data);

void llist_append(LList *list, int data);

void llist_insert_at(LList *list, int data, int pos);

void llist_delete_head(LList *list);

void llist_delete_tail(LList *list);

void llist_delete_value(LList *list, int data);

void llist_delete_at(LList *list, int pos);

void llist_print(const LList *list);

#endif // LLIST_H
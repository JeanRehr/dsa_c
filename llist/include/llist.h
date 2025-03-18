#ifndef LLIST_H
#define LLIST_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LList {
    int size;
    Node *head;
} LList;

void init(LList *list);

void free_list(LList *list);

Node* create_node(int data);

void prepend(LList *list, int data);

void append(LList *list, int data);

void insert_at(LList *list, int data, int pos);

void delete_head(LList *list);

void delete_tail(LList *list);

void delete_value(LList *list, int data);

void delete_at(LList *list, int pos);

void print_list(LList *list);

#endif
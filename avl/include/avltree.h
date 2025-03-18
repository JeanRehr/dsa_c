#ifndef AVLTREE_H
#define AVLTREE_H

typedef struct Node {
    int data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct AVLTree {
    Node *root;
} AVLTree;

void init(AVLTree *tree);

void free_tree(AVLTree *tree);

void free_subtree(Node *node);

int height(const Node *node);

void set_height(Node *node);

int bfactor(const Node *node);

Node* minimum(Node *node);

Node* create_node(int data);

void print(const AVLTree *tree);

void insert(AVLTree *tree, int data);

void remove_node(AVLTree *tree, int data);

void remove_subtree(AVLTree *tree, int data);

Node* rr(Node *node);

Node* ll(Node *node);

Node* rebal(Node *node);

void inorder(const AVLTree *tree);

#endif
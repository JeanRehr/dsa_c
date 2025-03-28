#ifndef AVLTREE_H
#define AVLTREE_H

typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

typedef struct AVLTree {
    AVLNode *root;
} AVLTree;

void avltree_init(AVLTree *tree);

void avltree_deinit(AVLTree *tree);

void avltree_print(const AVLTree *tree);

void avltree_insert(AVLTree *tree, int data);

void avltree_remove(AVLTree *tree, int data);

// Will remove all children of the node that contains data
void avltree_remove_stree(AVLTree *tree, int data);

void inorder(const AVLTree *tree);

#endif // AVLTREE_H
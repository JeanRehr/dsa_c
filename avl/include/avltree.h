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

void avltree_free_stree(AVLNode *node);

int avlnode_height(const AVLNode *node);

void avlnode_set_height(AVLNode *node);

int avlnode_bfactor(const AVLNode *node);

AVLNode* avltree_minimum(const AVLNode *node);

AVLNode* avltree_create_node(int data);

void avltree_print(const AVLTree *tree);

void avltree_insert(AVLTree *tree, int data);

void avltree_remove(AVLTree *tree, int data);

void avltree_remove_stree(AVLTree *tree, int data);

AVLNode* rr(AVLNode *node);

AVLNode* ll(AVLNode *node);

AVLNode* rebal(AVLNode *node);

void inorder(const AVLTree *tree);

#endif // AVLTREE_H
#include <stdio.h>
#include <stdlib.h>

#include "avltree.h"

void avltree_init(AVLTree *tree)
{
    tree->root = NULL;
}

void avltree_deinit(AVLTree *tree)
{
    avltree_free_stree(tree->root);
    tree->root = NULL;
}

void avltree_free_stree(AVLNode *node)
{
    if (node != NULL) {
        avltree_free_stree(node->left);
        avltree_free_stree(node->right);
        free(node);
    }
}

int avlnode_height(const AVLNode *node)
{
    return node == NULL ? 0 : node->height;
}

void avlnode_set_height(AVLNode *node)
{
    int left_height = avlnode_height(node->left);
    int right_height = avlnode_height(node->right);
    node->height = 1 + ((left_height > right_height) ? left_height : right_height);
}

int avlnode_bfactor(const AVLNode *node)
{
    return node == NULL ? 0 : avlnode_height(node->left) - avlnode_height(node->right);
}

AVLNode* avltree_minimum(AVLNode *node)
{
    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

AVLNode* avltree_create_node(int data)
{
    AVLNode *new_node = (AVLNode*)malloc(sizeof(AVLNode));
    if (new_node == NULL) {
        printf("Failed to allocate memory.\n");
        exit(-1);
    }

    new_node->data = data;
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void avltree_print_stree(const AVLNode *node, int lvl) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < lvl; i++) {
        printf("    ");
    }

    printf("%d\n", node->data);

    int nextlvl = lvl + 1;

    if (node->left != NULL) {
        avltree_print_stree(node->left, nextlvl);
    } else {
        for (int i = 0; i < nextlvl; i++) {
            printf("    ");
        }
        printf("_\n");
    }

    if (node->right != NULL) {
        avltree_print_stree(node->right, nextlvl);
    } else {
        for (int i = 0; i < nextlvl; i++) {
            printf("    ");
        }
        printf("_\n");
    }
}

void avltree_print(const AVLTree *tree) {
    avltree_print_stree(tree->root, 0);
}

AVLNode* _avltree_insert(AVLNode *node, int data)
{
    if (node == NULL) {
        AVLNode *new_node = avltree_create_node(data);
        return new_node;
    }

    if (node->data == data) {
        return node;
    }

    if (data < node->data) {
        node->left = _avltree_insert(node->left, data);
    } else {
        node->right = _avltree_insert(node->right, data);
    }

    avlnode_set_height(node);
    return rebal(node);
}

void avltree_insert(AVLTree *tree, int data)
{
    tree->root = _avltree_insert(tree->root, data);
}

AVLNode* _avltree_remove(AVLNode *node, int data)
{
    if (node == NULL) {
        return node;
    }

    if (data < node->data) {
        _avltree_remove(node->left, data);
    } else if (data > node->data) {
        _avltree_remove(node->right, data);
    } else {
        if ((node->right == NULL) || (node->left == NULL)) { // check if one or no child
            AVLNode *tmp = (node->left != NULL) ? node->left : node->right;
            if (tmp == NULL) { // no child
                tmp = node;
                node = NULL;
            } else { // one child
                *node = *tmp; // deref to assign all its data correctly
            }
            free(tmp);
        } else { // two children
            AVLNode *tmp = avltree_minimum(node->right); // get the successor of the deleted node
            node->data = tmp->data; // assign the data in the temp to the node to be "deleted"
            node->right = _avltree_remove(node->right, tmp->data); // remove the successor of the node
        }
    }

    avlnode_set_height(node);
    return rebal(node);
}

void avltree_remove(AVLTree *tree, int data)
{
    tree->root = _avltree_remove(tree->root, data);
}

AVLNode* _avltree_remove_stree(AVLNode *node, int data)
{
    if (node == NULL) {
        printf("Value not found\n");
        return node;
    }

    if (data < node->data) {
        _avltree_remove_stree(node->left, data);
    } else if (data > node->data) {
        _avltree_remove_stree(node->right, data);
    } else {
        avltree_free_stree(node);
        node = NULL;
        return node;
    }

    avlnode_set_height(node);
    return rebal(node);
}

void avltree_remove_stree(AVLTree *tree, int data)
{
    tree->root = _avltree_remove_stree(tree->root, data);
}

// right-right case, left rotation
AVLNode* rr(AVLNode *node)
{
    AVLNode *left_node = node->left;
    AVLNode *right_left_node = left_node->right;

    left_node->right = node;
    node->left = right_left_node;

    avlnode_set_height(node);
    avlnode_set_height(left_node);
    return left_node;
}

// left-left case, right rotation
AVLNode* ll(AVLNode *node)
{
    AVLNode *right_node = node->right;
    AVLNode *left_right_node = right_node->left;

    right_node->left = node;
    node->right = left_right_node;

    avlnode_set_height(node);
    avlnode_set_height(right_node);
    return right_node;
}

AVLNode* rebal(AVLNode *node)
{
    int bal = avlnode_bfactor(node);

    if (bal > 1 && avlnode_bfactor(node->left) >= 0) {
        return rr(node);
    } else if (bal < -1 && avlnode_bfactor(node->right) <= 0) {
        return ll(node);
    } else if (bal > 1 && avlnode_bfactor(node->left) <= 0) {
        node->left = ll(node->left);
        return rr(node);
    } else if (bal < -1 && avlnode_bfactor(node->right) >= 0) {
        node->right = rr(node->right);
        return ll(node);
    }

    return node;
}

void _inorder(const AVLNode *node)
{
    if (node != NULL) {
        _inorder(node->left);
        printf("%d ", node->data);
        _inorder(node->right);
    }
}

void inorder(const AVLTree *tree)
{
    _inorder(tree->root);
    printf("\n");
}
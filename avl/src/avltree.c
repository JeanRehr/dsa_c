#include <stdio.h>
#include <stdlib.h>

#include "avltree.h"

int _avlnode_height(const AVLNode *node)
{
    return node == NULL ? 0 : node->height;
}

void _avlnode_set_height(AVLNode *node)
{
    int left_height = _avlnode_height(node->left);
    int right_height = _avlnode_height(node->right);
    node->height = 1 + ((left_height > right_height) ? left_height : right_height);
}

int _avlnode_bfactor(const AVLNode *node)
{
    return node == NULL ? 0 : _avlnode_height(node->left) - _avlnode_height(node->right);
}

AVLNode* _avltree_minimum(const AVLNode *node)
{
    while (node->left != NULL) {
        node = node->left;
    }

    return (AVLNode *) node; // the return type is a mutable pointer and needs to be casted
}

AVLNode* _avltree_create_node(int data)
{
    AVLNode *new_node = (AVLNode*)malloc(sizeof(AVLNode));
    if (new_node == NULL) {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// right-right case, left rotation
AVLNode* _rr(AVLNode *node)
{
    AVLNode *left_node = node->left;
    AVLNode *right_left_node = left_node->right;

    left_node->right = node;
    node->left = right_left_node;

    _avlnode_set_height(node);
    _avlnode_set_height(left_node);
    return left_node;
}

// left-left case, right rotation
AVLNode* _ll(AVLNode *node)
{
    AVLNode *right_node = node->right;
    AVLNode *left_right_node = right_node->left;

    right_node->left = node;
    node->right = left_right_node;

    _avlnode_set_height(node);
    _avlnode_set_height(right_node);
    return right_node;
}

AVLNode* _rebal(AVLNode *node)
{
    int bal = _avlnode_bfactor(node);

    if (bal > 1 && _avlnode_bfactor(node->left) >= 0) {
        return _rr(node);
    } else if (bal < -1 && _avlnode_bfactor(node->right) <= 0) {
        return _ll(node);
    } else if (bal > 1 && _avlnode_bfactor(node->left) <= 0) {
        node->left = _ll(node->left);
        return _rr(node);
    } else if (bal < -1 && _avlnode_bfactor(node->right) >= 0) {
        node->right = _rr(node->right);
        return _ll(node);
    }

    return node;
}

void avltree_init(AVLTree *tree)
{
    tree->root = NULL;
}

void _avltree_free_stree(AVLNode *node)
{
    if (node != NULL) {
        _avltree_free_stree(node->left);
        _avltree_free_stree(node->right);
        free(node);
    }
}

void avltree_deinit(AVLTree *tree)
{
    _avltree_free_stree(tree->root);
    tree->root = NULL;
}

void _avltree_print_stree(const AVLNode *node, int lvl) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < lvl; i++) {
        printf("    ");
    }

    printf("%d\n", node->data);

    int nextlvl = lvl + 1;

    if (node->left != NULL) {
        _avltree_print_stree(node->left, nextlvl);
    } else {
        for (int i = 0; i < nextlvl; i++) {
            printf("    ");
        }
        printf("_\n");
    }

    if (node->right != NULL) {
        _avltree_print_stree(node->right, nextlvl);
    } else {
        for (int i = 0; i < nextlvl; i++) {
            printf("    ");
        }
        printf("_\n");
    }
}

void avltree_print(const AVLTree *tree) {
    _avltree_print_stree(tree->root, 0);
}

AVLNode* _avltree_insert(AVLNode *node, int data)
{
    if (node == NULL) {
        AVLNode *new_node = _avltree_create_node(data);
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

    _avlnode_set_height(node);
    return _rebal(node);
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
            AVLNode *tmp = _avltree_minimum(node->right); // get the successor of the deleted node
            node->data = tmp->data; // assign the data in the temp to the node to be "deleted"
            node->right = _avltree_remove(node->right, tmp->data); // remove the successor of the node
        }
    }

    _avlnode_set_height(node);
    return _rebal(node);
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
        _avltree_free_stree(node);
        node = NULL;
        return node;
    }

    _avlnode_set_height(node);
    return _rebal(node);
}

void avltree_remove_stree(AVLTree *tree, int data)
{
    tree->root = _avltree_remove_stree(tree->root, data);
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
#include <stdio.h>
#include <stdlib.h>

#include "avltree.h"

/*
struct Node {
    int data;
    int height;
    Node *left;
    Node *right;
};

struct AVLTree {
    Node *root;
};
*/

void init(AVLTree *tree)
{
    tree->root = NULL;
}

void free_tree(AVLTree *tree)
{
    free_subtree(tree->root);
    tree->root = NULL;
}

void free_subtree(Node *node)
{
    if (node != NULL) {
        free_subtree(node->left);
        free_subtree(node->right);
        free(node);
    }
}

int height(const Node *node)
{
    return node == NULL ? 0 : node->height;
}

void set_height(Node *node)
{
    int left_height = height(node->left);
    int right_height = height(node->right);
    node->height = 1 + ((left_height > right_height) ? left_height : right_height);
}

int bfactor(const Node *node)
{
    return node == NULL ? 0 : height(node->left) - height(node->right);
}

Node* minimum(Node *node)
{
    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

Node* create_node(int data)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
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

void _print(const Node *node, int lvl) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < lvl; i++) {
        printf("    ");
    }

    printf("%d\n", node->data);

    int nextlvl = lvl + 1;

    if (node->left != NULL) {
        _print(node->left, nextlvl);
    } else {
        for (int i = 0; i < nextlvl; i++) {
            printf("    ");
        }
        printf("_\n");
    }

    if (node->right != NULL) {
        _print(node->right, nextlvl);
    } else {
        for (int i = 0; i < nextlvl; i++) {
            printf("    ");
        }
        printf("_\n");
    }
}

void print(const AVLTree *tree) {
    _print(tree->root, 0);
}

Node* _insert(Node *node, int data)
{
    if (node == NULL) {
        Node *new_node = create_node(data);
        return new_node;
    }

    if (node->data == data) {
        return node;
    }

    if (data < node->data) {
        node->left = _insert(node->left, data);
    } else {
        node->right = _insert(node->right, data);
    }

    set_height(node);
    return rebal(node);
}

void insert(AVLTree *tree, int data)
{
    tree->root = _insert(tree->root, data);
}

Node* _remove_node(Node *node, int data)
{
    if (node == NULL) {
        return node;
    }

    if (data < node->data) {
        _remove_node(node->left, data);
    } else if (data > node->data) {
        _remove_node(node->right, data);
    } else {
        if ((node->right == NULL) || (node->left == NULL)) { // check if one or no child
            Node *tmp = (node->left != NULL) ? node->left : node->right;
            if (tmp == NULL) { // no child
                tmp = node;
                node = NULL;
            } else { // one child
                *node = *tmp; // deref to assign all its data correctly
            }
            free(tmp);
        } else { // two children
            Node *tmp = minimum(node->right); // get the successor of the deleted node
            node->data = tmp->data; // assign the data in the temp to the node to be "deleted"
            node->right = _remove_node(node->right, tmp->data); // remove the successor of the node
        }
    }

    set_height(node);
    return rebal(node);
}

void remove_node(AVLTree *tree, int data)
{
    tree->root = _remove_node(tree->root, data);
}

Node* _remove_subtree(Node *node, int data)
{
    if (node == NULL) {
        printf("Value not found\n");
        return node;
    }

    if (data < node->data) {
        _remove_subtree(node->left, data);
    } else if (data > node->data) {
        _remove_subtree(node->right, data);
    } else {
        free_subtree(node);
        node = NULL;
        return node;
    }

    set_height(node);
    return rebal(node);
}

void remove_subtree(AVLTree *tree, int data)
{
    tree->root = _remove_subtree(tree->root, data);
}

// right-right case, left rotation
Node* rr(Node *node)
{
    Node *left_node = node->left;
    Node *right_left_node = left_node->right;

    left_node->right = node;
    node->left = right_left_node;

    set_height(node);
    set_height(left_node);
    return left_node;
}

// left-left case, right rotation
Node* ll(Node *node)
{
    Node *right_node = node->right;
    Node *left_right_node = right_node->left;

    right_node->left = node;
    node->right = left_right_node;

    set_height(node);
    set_height(right_node);
    return right_node;
}

Node* rebal(Node *node)
{
    int bal = bfactor(node);

    if (bal > 1 && bfactor(node->left) >= 0) {
        return rr(node);
    } else if (bal < -1 && bfactor(node->right) <= 0) {
        return ll(node);
    } else if (bal > 1 && bfactor(node->left) <= 0) {
        node->left = ll(node->left);
        return rr(node);
    } else if (bal < -1 && bfactor(node->right) >= 0) {
        node->right = rr(node->right);
        return ll(node);
    }

    return node;
}

void _inorder(const Node *node)
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
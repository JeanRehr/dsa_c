#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "avltree.h"

void test_create_node()
{
    Node *node = create_node(10);
    assert(node != NULL);
    assert(node->data == 10);
    assert(node->height == 1);
    assert(node->left == NULL);
    assert(node->right == NULL);
    free(node);
    printf("test_create_node passed.\n");
}

void test_insert()
{
    AVLTree tree;
    init(&tree);

    insert(&tree, 10);
    assert(tree.root != NULL);
    assert(tree.root->data == 10);
    assert(tree.root->height == 1);

    insert(&tree, 10);
    assert(tree.root->data == 10);
    assert(tree.root->left == NULL);
    assert(tree.root->right == NULL);

    insert(&tree, 20);
    assert(tree.root->right != NULL);
    assert(tree.root->right->data == 20);
    assert(tree.root->right->height == 1);
    assert(tree.root->height == 2);

    insert(&tree, 5);
    assert(tree.root->left != NULL);
    assert(tree.root->left->data == 5);
    assert(tree.root->right->height == 1);
    assert(tree.root->height == 2);

    insert(&tree, 4);
    assert(tree.root->left->left != NULL);
    assert(tree.root->left->left->data == 4);
    assert(tree.root->left->left->height == 1);
    assert(tree.root->left->height == 2);
    assert(tree.root->height == 3);

    printf("test_insert passed.\n");
    free_tree(&tree);
}

void test_remove()
{
    AVLTree tree;
    init(&tree);

    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 5);
    insert(&tree, 4);

    remove_node(&tree, 1000);
    remove_node(&tree, 5);
    assert(tree.root->left->data != 5);
    assert(tree.root->left->data == 4);

    printf("test_remove passed.\n");
    free_tree(&tree);
}

void test_remove_subtree()
{
    AVLTree tree;
    init(&tree);

    insert(&tree, 10);
    insert(&tree, 5);
    insert(&tree, 15);
    remove_subtree(&tree, tree.root->data);

    assert(tree.root == NULL);

    printf("test_remove_subtree passed.\n");
    free_tree(&tree);
}

void test_balancing()
{
    AVLTree tree;
    init(&tree);

    insert(&tree, 5);
    assert(tree.root->data == 5);
    insert(&tree, 10);
    assert(tree.root->data == 5);
    insert(&tree, 15);
    assert(tree.root->data == 10);
    assert(tree.root->left->data == 5);
    assert(tree.root->right->data == 15);
    remove_subtree(&tree, tree.root->data);

    insert(&tree, 15);
    assert(tree.root->data == 15);
    insert(&tree, 10);
    assert(tree.root->data == 15);
    insert(&tree, 5);
    assert(tree.root->data == 10);
    assert(tree.root->left->data == 5);
    assert(tree.root->right->data == 15);
    remove_subtree(&tree, tree.root->data);

/*
       4                 2
      / \               / \
     2   6             1   4
    / \       =>      /   / \
   1   3            -1   3   6
  /
-1
*/
    insert(&tree, 4);
    insert(&tree, 2);
    insert(&tree, 6);
    insert(&tree, 1);
    insert(&tree, 3);
    assert(tree.root->data == 4);
    assert(tree.root->left->data == 2);
    assert(tree.root->right->data == 6);
    assert(tree.root->left->left->data == 1);
    assert(tree.root->left->right->data == 3);
    
    insert(&tree, -1);
    assert(tree.root->data == 2);
    assert(tree.root->left->data == 1);
    assert(tree.root->right->data == 4);
    assert(tree.root->right->left->data == 3);
    remove_subtree(&tree, tree.root->data);

/*
  4                     6
 / \                   / \
2   6                 4   7
   / \       =>      / \   \
  5   7             2   5   8
       \
        8
*/
    insert(&tree, 4);
    insert(&tree, 2);
    insert(&tree, 6);
    insert(&tree, 5);
    insert(&tree, 7);
    assert(tree.root->data == 4);
    assert(tree.root->left->data == 2);
    assert(tree.root->right->data == 6);
    assert(tree.root->right->left->data == 5);
    assert(tree.root->right->right->data == 7);
    
    insert(&tree, 8);
    assert(tree.root->data == 6);
    assert(tree.root->left->data == 4);
    assert(tree.root->right->data == 7);
    assert(tree.root->left->right->data == 5);

    printf("test_balancing passed.\n");
    free_tree(&tree);
}

void test_free_tree()
{
    AVLTree tree;
    init(&tree);

    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 5);

    free_tree(&tree);
    assert(tree.root == NULL);

    printf("test_free_tree passed.\n");
}

void all_tests_run()
{
    test_create_node();    
    test_insert();    
    test_remove();    
    test_remove_subtree();    
    test_balancing();    
    test_free_tree();
}

int main(void)
{
    all_tests_run();
    return 0;
}
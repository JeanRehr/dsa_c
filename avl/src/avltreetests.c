#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "avltree.h"

void test_avltree_create_node()
{
    AVLNode *node = avltree_create_node(10);
    assert(node != NULL);
    assert(node->data == 10);
    assert(node->height == 1);
    assert(node->left == NULL);
    assert(node->right == NULL);
    free(node);
    printf("test_avltree_create_node passed.\n");
}

void test_avltree_insert()
{
    AVLTree tree;
    avltree_init(&tree);

    avltree_insert(&tree, 10);
    assert(tree.root != NULL);
    assert(tree.root->data == 10);
    assert(tree.root->height == 1);

    avltree_insert(&tree, 10);
    assert(tree.root->data == 10);
    assert(tree.root->left == NULL);
    assert(tree.root->right == NULL);

    avltree_insert(&tree, 20);
    assert(tree.root->right != NULL);
    assert(tree.root->right->data == 20);
    assert(tree.root->right->height == 1);
    assert(tree.root->height == 2);

    avltree_insert(&tree, 5);
    assert(tree.root->left != NULL);
    assert(tree.root->left->data == 5);
    assert(tree.root->right->height == 1);
    assert(tree.root->height == 2);

    avltree_insert(&tree, 4);
    assert(tree.root->left->left != NULL);
    assert(tree.root->left->left->data == 4);
    assert(tree.root->left->left->height == 1);
    assert(tree.root->left->height == 2);
    assert(tree.root->height == 3);

    printf("test_avltree_insert passed.\n");
    avltree_deinit(&tree);
}

void test_avltree_remove()
{
    AVLTree tree;
    avltree_init(&tree);

    avltree_insert(&tree, 10);
    avltree_insert(&tree, 20);
    avltree_insert(&tree, 5);
    avltree_insert(&tree, 4);

    avltree_remove(&tree, 1000);
    avltree_remove(&tree, 5);
    assert(tree.root->left->data != 5);
    assert(tree.root->left->data == 4);

    printf("test_avltree_remove passed.\n");
    avltree_deinit(&tree);
}

void test_avltree_remove_stree()
{
    AVLTree tree;
    avltree_init(&tree);

    avltree_insert(&tree, 10);
    avltree_insert(&tree, 5);
    avltree_insert(&tree, 15);
    avltree_remove_stree(&tree, tree.root->data);

    assert(tree.root == NULL);

    printf("test_avltree_remove_stree passed.\n");
    avltree_deinit(&tree);
}

void test_balancing()
{
    AVLTree tree;
    avltree_init(&tree);

    avltree_insert(&tree, 5);
    assert(tree.root->data == 5);
    avltree_insert(&tree, 10);
    assert(tree.root->data == 5);
    avltree_insert(&tree, 15);
    assert(tree.root->data == 10);
    assert(tree.root->left->data == 5);
    assert(tree.root->right->data == 15);
    avltree_remove_stree(&tree, tree.root->data);

    avltree_insert(&tree, 15);
    assert(tree.root->data == 15);
    avltree_insert(&tree, 10);
    assert(tree.root->data == 15);
    avltree_insert(&tree, 5);
    assert(tree.root->data == 10);
    assert(tree.root->left->data == 5);
    assert(tree.root->right->data == 15);
    avltree_remove_stree(&tree, tree.root->data);

/*
       4                 2
      / \               / \
     2   6             1   4
    / \       =>      /   / \
   1   3            -1   3   6
  /
-1
*/
    avltree_insert(&tree, 4);
    avltree_insert(&tree, 2);
    avltree_insert(&tree, 6);
    avltree_insert(&tree, 1);
    avltree_insert(&tree, 3);
    assert(tree.root->data == 4);
    assert(tree.root->left->data == 2);
    assert(tree.root->right->data == 6);
    assert(tree.root->left->left->data == 1);
    assert(tree.root->left->right->data == 3);
    
    avltree_insert(&tree, -1);
    assert(tree.root->data == 2);
    assert(tree.root->left->data == 1);
    assert(tree.root->right->data == 4);
    assert(tree.root->right->left->data == 3);
    avltree_remove_stree(&tree, tree.root->data);

/*
  4                     6
 / \                   / \
2   6                 4   7
   / \       =>      / \   \
  5   7             2   5   8
       \
        8
*/
    avltree_insert(&tree, 4);
    avltree_insert(&tree, 2);
    avltree_insert(&tree, 6);
    avltree_insert(&tree, 5);
    avltree_insert(&tree, 7);
    assert(tree.root->data == 4);
    assert(tree.root->left->data == 2);
    assert(tree.root->right->data == 6);
    assert(tree.root->right->left->data == 5);
    assert(tree.root->right->right->data == 7);
    
    avltree_insert(&tree, 8);
    assert(tree.root->data == 6);
    assert(tree.root->left->data == 4);
    assert(tree.root->right->data == 7);
    assert(tree.root->left->right->data == 5);

    printf("test_balancing passed.\n");
    avltree_deinit(&tree);
}

void test_avltree_deinit()
{
    AVLTree tree;
    avltree_init(&tree);

    avltree_insert(&tree, 10);
    avltree_insert(&tree, 20);
    avltree_insert(&tree, 5);

    avltree_deinit(&tree);
    assert(tree.root == NULL);

    printf("test_avltree_deinit passed.\n");
}

void test_avltree_print()
{
    AVLTree tree;
    avltree_init(&tree);

    printf("Adding 10.\n");
    avltree_insert(&tree, 10);
    printf("Adding 20.\n");
    avltree_insert(&tree, 20);
    printf("Adding 5.\n");
    avltree_insert(&tree, 5);
    printf("Printing tree:\n");
    avltree_print(&tree);

    avltree_deinit(&tree);
    printf("test_avltree_print passed.\n");
}

void all_tests_run()
{
    test_avltree_create_node();    
    test_avltree_insert();    
    test_avltree_remove();    
    test_avltree_remove_stree();    
    test_balancing();    
    test_avltree_deinit();
    test_avltree_print();
}

int main(void)
{
    all_tests_run();
    return EXIT_SUCCESS;
}
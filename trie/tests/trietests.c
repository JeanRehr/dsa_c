#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "trie.h"

void test_trie_init()
{
    Trie trie;
    trie_init(&trie);

    assert(trie.root != NULL);

    printf("test_trie_init passed.\n");
    trie_deinit(&trie);
}

void test_trie_deinit()
{
    Trie trie;
    trie_init(&trie);
    trie_deinit(&trie);
    assert(trie.root == NULL);
    printf("test_trie_deinit passed.\n");
}

void test_trie_insert()
{
    Trie trie;
    trie_init(&trie);

    trie_insert(&trie, "aaron");
    trie_insert(&trie, "ayrton");

    // aaron
    assert(trie.root->children[0] != NULL);
    assert(trie.root->children[0]->children[0] != NULL);
    assert(trie.root->children[0]->children[0]->children[17] != NULL);
    assert(trie.root->children[0]->children[0]->children[17]->children[14] != NULL);
    assert(trie.root->children[0]->children[0]->children[17]->children[14]->children[13] != NULL);
    assert(trie.root->children[0]->children[0]->children[17]->children[14]->children[13]->is_end == 1);

    // ayrton
    assert(trie.root->children[0] != NULL);
    assert(trie.root->children[0]->children[24] != NULL);
    assert(trie.root->children[0]->children[24]->children[17] != NULL);
    assert(trie.root->children[0]->children[24]->children[17]->children[19] != NULL);
    assert(trie.root->children[0]->children[24]->children[17]->children[19]->children[14] != NULL);
    assert(trie.root->children[0]->children[24]->children[17]->children[19]->children[14]->children[13] != NULL);
    assert(trie.root->children[0]->children[24]->children[17]->children[19]->children[14]->children[13]->is_end == 1);

    trie_deinit(&trie);
    printf("test_trie_insert passed.\n");
}

void test_trie_search()
{
    Trie trie;
    trie_init(&trie);

    trie_insert(&trie, "abase");
    trie_insert(&trie, "abased");
    trie_insert(&trie, "abasement");
    assert(trie_search(&trie, "abase") == 1);
    assert(trie_search(&trie, "abased") == 1);
    assert(trie_search(&trie, "abasement") == 1);
    assert(trie_search(&trie, "aba") == 0);
    assert(trie_search(&trie, "world") == 0);

    trie_deinit(&trie);
    printf("test_trie_search passed.\n");
}

void test_trie_print()
{
    Trie trie;
    trie_init(&trie);

    printf("Inserting world.\n");
    trie_insert(&trie, "world");
    printf("Inserting wow.\n");
    trie_insert(&trie, "wow");
    printf("Inserting wanna.\n");
    trie_insert(&trie, "wanna");
    printf("Inserting about.\n");
    trie_insert(&trie, "about");
    printf("Printing Trie.\n");
    trie_print(&trie);

    trie_deinit(&trie);
    printf("test_trie_print passed.\n");
}

void run_all_tests()
{
    test_trie_init();
    test_trie_deinit();
    test_trie_insert();
    test_trie_search();
    test_trie_print();
}

int main (void)
{
    run_all_tests();
    return 0;
}
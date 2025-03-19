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

void run_all_tests()
{
    test_trie_init();
    test_trie_deinit();
}

int main (void)
{
    run_all_tests();
    return 0;
}
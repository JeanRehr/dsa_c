#include <stdlib.h>

#include "trie.h"

void trie_init(Trie *trie)
{
    trie->root = (TrieNode *)malloc(sizeof(TrieNode));
    trie->root->is_end = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        trie->root->children[i] = NULL;
    }
}

void _trie_deinit(TrieNode *node)
{
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (node->children[i] != NULL) {
            _trie_deinit(node->children[i]);
        }
    }

    free(node);
}

void trie_deinit(Trie *trie)
{
    if (trie->root == NULL) {
        return;
    }

    _trie_deinit(trie->root);
    trie->root = NULL;
}

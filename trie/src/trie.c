#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trie.h"

TrieNode* _trie_create_node()
{
    TrieNode *new_node = (TrieNode *)malloc(sizeof(TrieNode));
    new_node->is_end = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        new_node->children[i] = NULL;
    }

    return new_node;
}

void trie_init(Trie *trie)
{
    trie->root = _trie_create_node();
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

void trie_insert(Trie *trie, const char *key)
{
    if (trie->root == NULL) {
        return;
    }

    TrieNode *current = trie->root;

    while (*key != '\0') {
        int index = *key - 'a';

        // Prevent buffer under/overflow
        if (index < 0 || index > ALPHABET_SIZE) {
            return; // Ignore invalid characters.
        }

        if (current->children[index] == NULL) {
            TrieNode *new_node = _trie_create_node();
            current->children[index] = new_node;
        }
        current = current->children[index];
        key++;
    }
    current->is_end = 1;
}

int trie_search(const Trie *trie, const char *key)
{
    if (trie->root == NULL) {
        return 0;
    }

    TrieNode *current = trie->root;
    int index;

    while (*key != '\0') {
        int index = *key - 'a';
        if (current->children[index] == NULL) {
            return 0;
        }
        current = current->children[index];
        key++;
    }

    return current->is_end;
}
    }

    return 0;
}

int __max_depth(const TrieNode *node, int lvl)
{
    int max_depth = lvl;

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (node->children[i] != NULL) {
            int child_depth = __max_depth(node->children[i], lvl + 1);
            if (child_depth > max_depth) {
                max_depth = child_depth;
            }
        }
    }

    return max_depth;
}
int _max_depth(const Trie *trie)
{
    return __max_depth(trie->root, 0);
}

void _trie_print(const TrieNode *node, char buf[], int lvl)
{
    if (node->is_end == 1) {
        buf[lvl] = '\0';
        printf("%s\n", buf); // Print the current word if it's a terminal node.
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (node->children[i] != NULL) {
            buf[lvl] = i + 'a'; // Build prefix
            _trie_print(node->children[i], buf, lvl + 1);
        }
    }
}

void trie_print(const Trie *trie)
{
    const size_t len = _max_depth(trie);
    char buf[len + 1]; // +1 for the null byte
    memset(buf, 0, len * sizeof(char));
    _trie_print(trie->root, buf, 0);
}
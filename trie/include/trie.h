#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int is_end;
} TrieNode;

typedef struct Trie {
    TrieNode *root;
} Trie;

void trie_init(Trie *trie);

void trie_deinit(Trie *trie);

void trie_insert(Trie *trie, const char *key);

int trie_search(const Trie *trie, const char *key);

void trie_remove(Trie *trie, const char *key);

void trie_print(const Trie *trie);

#endif // TRIE_H
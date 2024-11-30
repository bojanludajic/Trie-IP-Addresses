#ifndef TRIE_H
#define TRIE_H

#define IS_END 1
#define NOT_END 0

typedef struct TrieNode {
    struct TrieNode* children[2];
    int isEnd;
} TrieNode;

TrieNode* createNode();
void enterAddress(TrieNode* root, int* address);
void print(TrieNode* root);
void freeTrie(TrieNode* node);
int* parse(char* ip);
int searchTrie(char* ip, TrieNode* root);

#endif

#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TrieNode* createNode() {
    TrieNode* newNode = malloc(sizeof(TrieNode));
    newNode->isEnd = NOT_END;
    newNode->children[0] = NULL;
    newNode->children[1] = NULL;
    return newNode;
}

void enterAddress(TrieNode* root, int* address) {
    TrieNode* cur = root;

    for (int i = 0; i < 32; i++) {
        int binary = address[i];
        if (cur->children[binary] == NULL) {
            cur->children[binary] = createNode();
        }
        cur = cur->children[binary];
    }

    cur->isEnd = IS_END;
}

void printBinaryToIP(int* binary) {
    for (int i = 0; i < 4; i++) {
        int octet = 0;
        for (int j = 0; j < 8; j++) {
            octet = (octet << 1) | binary[i * 8 + j];
        }
        printf("%d", octet);
        if (i < 3) printf(".");
    }
    printf("\n");
}

void printAddress(TrieNode* node, int* prefix, int depth) {
    if (node == NULL) return;

    if (node->isEnd) {
        printBinaryToIP(prefix);
    }

    if (node->children[0] != NULL) {
        prefix[depth] = 0;
        printAddress(node->children[0], prefix, depth + 1);
    }
    if (node->children[1] != NULL) {
        prefix[depth] = 1;
        printAddress(node->children[1], prefix, depth + 1);
    }
}

void print(TrieNode* root) {
    printf("Available IP addresses: \n");
    int prefix[32];
    printAddress(root, prefix, 0);
}

void freeTrie(TrieNode* node) {
    if (node->children[0] != NULL) {
        freeTrie(node->children[0]);
    }
    if (node->children[1] != NULL) {
        freeTrie(node->children[1]);
    }
    free(node);
}

int* parse(char* ip) {
    char ip_copy[strlen(ip) + 1];
    strcpy(ip_copy, ip);

    int n1, n2, n3, n4;
    sscanf(ip_copy, "%d.%d.%d.%d", &n1, &n2, &n3, &n4);
    int octets[4] = {n1, n2, n3, n4};

    int* binary = malloc(32 * sizeof(int));
    int h = 0;
    for (int i = 0; i < 4; i++) {
        for (int k = 7; k >= 0; k--) {
            binary[h] = (octets[i] >> k) & 1;
            h++;
        }
    }

    return binary;
}

int searchTrie(char* ip, TrieNode* root) {
    int* binary = parse(ip);
    TrieNode* cur = root;

    for (int i = 0; i < 32; i++) {
        cur = cur->children[binary[i]];
        if (cur == NULL) return 0;
    }

    return 1;
}

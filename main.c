#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_END 1
#define NOT_END 0

typedef struct {
    struct TrieNode* children[2];
    int isEnd;
} TrieNode;

TrieNode* createNode() {
    TrieNode* newNode = malloc(sizeof(TrieNode));
    newNode->isEnd = NOT_END;
    newNode->children[0] = NULL;
    newNode->children[1] = NULL;
    return newNode;
}

void enterAddress(TrieNode* root, int* address) {
    TrieNode* cur = root;

    for(int i = 0; i < 32; i++) {
        int binary = address[i];
        if(cur->children[binary] == NULL) {
            cur->children[binary] = createNode();
        }
        cur = cur->children[binary];
    }

    cur->isEnd = IS_END;
}

void printBinaryToIP(int* binary) {
    for(int i = 0; i < 4; i++) {
        int octet = 0;
        for(int j = 0; j < 8; j++) {
            octet = (octet << 1) | binary[i * 8 + j];
        }
        printf("%d", octet);
        if(i < 3) printf(".");
    }
    printf("\n");
}

void printAddress(TrieNode* node, int* prefix, int depth) {
    if(node == NULL) return;

    if(node->isEnd) {
        printBinaryToIP(prefix);
    }

    if(node->children[0] != NULL) {
        prefix[depth] = 0;
        printAddress(node->children[0], prefix, depth + 1);
    }
    if(node->children[1] != NULL) {
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
    if(node->children[0] != NULL) {
        freeTrie(node->children[0]);
    }
    if(node->children[1] != NULL) {
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
    for(int i = 0; i < 4; i++) {
        for(int k = 7; k >= 0; k--) {
            binary[h] = (octets[i] >> k) & 1;
            h++;
        }
    }

    return binary;
}

int searchTrie(char* ip, TrieNode* root) {
    int* binary = parse(ip);
    TrieNode* cur = root;

    for(int i = 0; i < 32; i++) {
        cur = cur->children[binary[i]];
        if(cur == NULL) return 0;
    }

    return 1;
}

void initTrie(TrieNode* root) {
    char ip1[] = "192.168.1.20";
    char ip2[] = "192.168.1.23";
    char ip3[] = "192.168.1.24";
    char ip4[] = "192.168.1.25";

    int* binary = parse(ip1);
    enterAddress(root, parse(ip1));
    binary = parse(ip2);
    enterAddress(root, parse(ip2));
    binary = parse(ip3);
    enterAddress(root, parse(ip3));
    binary = parse(ip4);
    enterAddress(root, parse(ip4));

    free(binary);
}

int main(void) {
    TrieNode* root = createNode();
    char option;

    initTrie(root);

    do {
        printf("Select an option: \n"
               "1:IP Lookup\n"
               "2:Display all available addresses\n"
               "E: End program\n"
               );
        scanf("%c", &option);
        getchar();
        switch(option) {
            case '1':
                printf("Enter IP to search: ");
                char searchIP[15];
                scanf("%s", searchIP);
                getchar();
                if(searchTrie(searchIP, root)) {
                    printf("Address found\n");
                } else {
                    printf("Address not found, would you like to insert it? (Y/N): ");
                    char insertq;
                    scanf("%c", &insertq);
                    getchar();
                    if(insertq == 'Y') {
                        int* binary = parse(searchIP);
                        enterAddress(root, parse(searchIP));
                        free(binary);
                    }
                }
                break;
            case '2':
                print(root);
                break;
            case 'E':
                printf("Exiting program\n");
                break;
            default:
                printf("Non-existing option selected\n");
                break;
        }
    } while(option != 'E');

    freeTrie(root);

    return 0;
}

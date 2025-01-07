#include <stdio.h>
#include <stdlib.h>

#include "trie.h"


void initTrie(TrieNode* root) {
    char ip1[] = "192.168.1.20";
    char ip2[] = "192.168.1.23";
    char ip3[] = "192.168.1.24";
    char ip4[] = "192.168.1.25";

    int* binary = parse(ip1);
    enterAddress(root, binary);
    binary = parse(ip2);
    enterAddress(root, binary);
    binary = parse(ip3);
    enterAddress(root, binary);
    binary = parse(ip4);
    enterAddress(root, binary);

    free(binary);
}

int main(void) {
    TrieNode* root = createNode();
    char option;

    initTrie(root);

    do {
        printf("Select an option: \n"
               "1: IP Lookup\n"
               "2: Display all available addresses\n"
               "3: Display addresses in subnet:\n"
               "E: End program\n"
               );
        scanf("%c", &option);
        getchar();
        char cidr[18];
        switch(option) {
            case '1':
                printf("Enter IP to search: ");
                char searchIP[15];
                scanf("%s", searchIP);
                getchar();
                int searchResult = searchTrie(searchIP, root);
                if(searchResult == 1) {
                    printf("Address found\n");
                } else if(searchResult == 0) {
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
                printAvailableAddresses(root);
                break;
            case '3':
                printf("Enter CIDR:\n");
                scanf("%s", cidr);
                getchar();
                printCIDR(cidr, root);
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

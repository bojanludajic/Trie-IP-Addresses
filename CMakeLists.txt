cmake_minimum_required(VERSION 3.29)
project(TrieIPLogging C)

set(CMAKE_C_STANDARD 11)

add_executable(TrieIPLogging main.c
        Trie.c
        trie.h)

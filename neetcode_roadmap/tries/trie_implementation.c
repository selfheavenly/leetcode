#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct Trie_Node {
    struct Trie_Node* children[ALPHABET_SIZE];
    bool is_end;
} Trie_Node;

typedef struct {
    Trie_Node* root;
} Trie;

Trie_Node* create_node() {
    Trie_Node* node = (Trie_Node*)malloc(sizeof(Trie_Node));
    if (!node) return NULL;
    
    node->is_end = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    
    return node;
}

Trie* trie_create() {
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    trie->root = create_node();
    return trie;
}

void trie_insert(Trie* obj, const char* word) {
    Trie_Node* node = obj->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL) 
            node->children[index] = create_node();
        node = node->children[index];
    }
    node->is_end = true;
}

bool trie_search(Trie* obj, const char* word) {
    Trie_Node* node = obj->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL) return false;
        node = node->children[index];
    }
    return node->is_end;
}

bool trie_starts_with(Trie* obj, const char* prefix) {
    Trie_Node* node = obj->root;
    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';
        if (node->children[index] == NULL) return false;
        node = node->children[index];
    }
    return true;
}

void free_trie_node(Trie_Node* node) {
    if (!node) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        free_trie_node(node->children[i]);
    free(node);
}

void trie_free(Trie* obj) {
    free_trie_node(obj->root);
    free(obj);
}
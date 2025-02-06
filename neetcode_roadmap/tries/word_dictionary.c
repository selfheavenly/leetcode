#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct Word_Dictionary {
    struct Word_Dictionary* children[ALPHABET_SIZE];
    bool is_end_of_word;
} Word_Dictionary;

Word_Dictionary* word_dictionary_create() {
    return (Word_Dictionary*)calloc(1, sizeof(Word_Dictionary));
}

void word_dictionary_add_word(Word_Dictionary* dict, char* word) {
    while (*word) {
        int index = *word - 'a';
        if (!dict->children[index]) {
            dict->children[index] = (Word_Dictionary*)calloc(1, sizeof(Word_Dictionary));
        }
        dict = dict->children[index];
        word++;
    }
    dict->is_end_of_word = true;
}

bool word_dictionary_search(Word_Dictionary* dict, char* word) {
    while (*word) {
        if (*word == '.') {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (dict->children[i] && word_dictionary_search(dict->children[i], word + 1)) {
                    return true;
                }
            }
            return false;
        } else {
            int index = *word - 'a';
            if (!dict->children[index]) {
                return false;
            }
            dict = dict->children[index];
        }
        word++;
    }
    return dict->is_end_of_word;
}

void word_dictionary_free(Word_Dictionary* dict) {
    if (!dict) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (dict->children[i]) {
            word_dictionary_free(dict->children[i]);
        }
    }
    free(dict);
}

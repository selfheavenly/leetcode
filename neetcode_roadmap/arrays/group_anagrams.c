#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key[26];
    char** group;
    int groupSize;
    int groupCapacity;
} HashNode;

typedef struct {
    HashNode* nodes;
    int size;
    int capacity;
} HashMap;

HashMap* initHashMap(int capacity) {
    HashMap* map = malloc(sizeof(HashMap));
    map->nodes = calloc(capacity, sizeof(HashNode));
    map->size = 0;
    map->capacity = capacity;
    return map;
}

int hashFunction(const int* key, int capacity) {
    unsigned long hash = 5381;
    for (int i = 0; i < 26; i++) {
        hash = ((hash << 5) + hash) + key[i];
    }
    return hash % capacity;
}

void resizeHashMap(HashMap* map) {
    int newCapacity = map->capacity * 2;
    HashNode* newNodes = calloc(newCapacity, sizeof(HashNode));

    for (int i = 0; i < map->capacity; i++) {
        if (map->nodes[i].group != NULL) {
            int newIndex = hashFunction(map->nodes[i].key, newCapacity);
            while (newNodes[newIndex].group != NULL) {
                newIndex = (newIndex + 1) % newCapacity;
            }
            newNodes[newIndex] = map->nodes[i];
        }
    }

    free(map->nodes);
    map->nodes = newNodes;
    map->capacity = newCapacity;
}

void addToHashMap(HashMap* map, const int* key, const char* value, int hashIndex) {
    int index = hashIndex;

    while (map->nodes[index].group != NULL) {
        if (memcmp(map->nodes[index].key, key, 26 * sizeof(int)) == 0) {
            // Key exists, add to the group
            if (map->nodes[index].groupSize == map->nodes[index].groupCapacity) {
                map->nodes[index].groupCapacity *= 2;
                map->nodes[index].group = realloc(map->nodes[index].group, map->nodes[index].groupCapacity * sizeof(char*));
            }
            map->nodes[index].group[map->nodes[index].groupSize++] = (char*)value;
            return;
        }
        index = (index + 1) % map->capacity;
    }

    // Key does not exist, create a new group
    memcpy(map->nodes[index].key, key, 26 * sizeof(int));
    map->nodes[index].group = malloc(2 * sizeof(char*));
    map->nodes[index].group[0] = (char*)value;
    map->nodes[index].groupSize = 1;
    map->nodes[index].groupCapacity = 2;
    map->size++;
    if ((double)map->size / map->capacity > 0.7) {
        resizeHashMap(map);
    }
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    HashMap* map = initHashMap(strsSize * 2);

    for (int i = 0; i < strsSize; i++) {
        int freq[26] = {0};

        // Count character frequencies
        for (int j = 0; strs[i][j] != '\0'; j++) {
            freq[strs[i][j] - 'a']++;
        }

        int hashIndex = hashFunction(freq, map->capacity);
        addToHashMap(map, freq, strs[i], hashIndex);
    }

    // Prepare the result
    char*** result = malloc(map->size * sizeof(char**));
    *returnColumnSizes = malloc(map->size * sizeof(int));
    *returnSize = map->size;

    int count = 0;
    for (int i = 0; i < map->capacity; i++) {
        if (map->nodes[i].group != NULL) {
            result[count] = map->nodes[i].group;
            (*returnColumnSizes)[count] = map->nodes[i].groupSize;
            count++;
        }
    }

    return result;
}
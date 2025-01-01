#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* keys;
    bool* occupied;
    int capacity;
} HashMap;

HashMap* initHashMap(int capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->keys = (int *)malloc(capacity * sizeof(int));
    map->occupied = (bool *)calloc(capacity, sizeof(bool));
    map->capacity = capacity;
    return map;
}

void freeHashMap(HashMap *map) {
    free(map->keys);
    free(map->occupied);
    free(map);
}

int hashFunction(int key, int capacity) {
    uint64_t hash = key;
    hash = (hash ^ (hash >> 16)) * 0x45d9f3b; // Mix bits
    hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
    hash = hash ^ (hash >> 16);
    return abs((int)(hash % capacity));
}

bool insertHashNode(HashMap *map, int key) {
    int originalIndex = hashFunction(key, map->capacity);
    int index = originalIndex;
    int i = 1;

    while (map->occupied[index]) {
        if (map->keys[index] == key) {
            return true; // Duplicate found
        }
        // Quadratic probing: reduce clustering
        index = (originalIndex + i * i) % map->capacity;
        i++;
        if (index == originalIndex) {
            break; // Full loop completed, no space left
        }
    }

    map->keys[index] = key;
    map->occupied[index] = true;

    return false;
}


bool containsDuplicate(int* nums, int numsSize) {
    if (numsSize <= 1) return false;

    HashMap *map = initHashMap(numsSize * 2);

    for (int i = 0; i < numsSize; i++) {
        if(insertHashNode(map,nums[i])) {
            freeHashMap(map);
            return true;
        }
    }
    return false;
}
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int* keys;
    int* ids;
    bool* occupied;
    int capacity;
} HashMap;

HashMap* initHashMap(int capacity) {
    HashMap* map    = (HashMap*)malloc(sizeof(HashMap));
    map->keys       = malloc(capacity * sizeof(int));
    map->ids        = malloc(capacity * sizeof(int));
    map->occupied   = calloc(capacity, sizeof(bool));
    map->capacity   = capacity;
    return map;
}

int hashFunction(int key, int capacity) {
    uint64_t hash = key;
    hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
    hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
    hash = hash ^ (hash >> 16);
    return abs((int)(hash % capacity));
}

void insertHashNode(HashMap *map, int key, int id) {
    int originalIndex = hashFunction(key, map->capacity);
    int index = originalIndex;
    int i = 1;

    while (map->occupied[index]) {
        index = (originalIndex + i * i) % map->capacity;
        i++;
    }

    map->keys[index] = key;
    map->ids[index] = id;
    map->occupied[index] = true;
}

int contains(HashMap* map, int key) {
    int originalIndex = hashFunction(key, map->capacity);
    int index = originalIndex;
    int i = 1;

    while (map->occupied[index]) {
        if (map->keys[index] == key) {
            return map->ids[index];
        }
        index = (originalIndex + i * i) % map->capacity;
        i++;
    }

    return -1;
}

void freeHashMap(HashMap* map) {
    free(map->keys);
    free(map->ids);
    free(map->occupied);
    free(map);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashMap* stored = initHashMap(2 * numsSize);
    int* solution = malloc(2 * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        int desiredId = contains(stored, target - nums[i]);
        if (desiredId != -1) {
            solution[0] = desiredId;
            solution[1] = i;
            *returnSize = 2;
            freeHashMap(stored);
            return solution;
        }
        insertHashNode(stored, nums[i], i);
    }

    freeHashMap(stored);
    return NULL;
}
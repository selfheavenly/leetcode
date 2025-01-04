#include <stdlib.h>
#include <stdbool.h>

typedef enum { EMPTY, OCCUPIED, REMOVED } SlotState;

typedef struct {
    int* table;
    SlotState* state;
    int capacity;
    int size;
} HashSet;

HashSet* setCreate(int capacity) {
    HashSet* set = malloc(sizeof(HashSet));
    set->table = calloc(capacity, sizeof(int));
    set->state = calloc(capacity, sizeof(SlotState));
    set->capacity = capacity;
    set->size = 0;
    return set;
}

void setFree(HashSet* set) {
    free(set->table);
    free(set->state);
    free(set);
}

int hashFunction(int key, int capacity) {
    uint64_t hash = (uint64_t)key * 2654435761U;
    hash = hash % capacity;
    return (int)hash;
}

bool setInsert(HashSet* set, int key) {
    int index = hashFunction(key, set->capacity);
    int originalIndex = index;
    int i = 1;

    while (set->state[index] == OCCUPIED) {
        if (set->table[index] == key) {
            return false;
        }
        index = (originalIndex + ++i) % set->capacity;
    }

    set->table[index] = key;
    set->state[index] = OCCUPIED;
    set->size++;
    return true;
}

bool setContains(HashSet* set, int key) {
    int index = hashFunction(key, set->capacity);
    int originalIndex = index;
    int i = 1;

    while (set->state[index] != EMPTY) {
        if (set->state[index] == OCCUPIED && set->table[index] == key) {
            return true;
        }
        index = (originalIndex + ++i) % set->capacity;
    }

    return false;
}

void setRemove(HashSet* set, int key) {
    int index = hashFunction(key, set->capacity);
    int originalIndex = index;
    int i = 1;

    while (set->state[index] != EMPTY) {
        if (set->state[index] == OCCUPIED && set->table[index] == key) {
            set->state[index] = REMOVED;
            return;
        }
        index = (originalIndex + i * i) % set->capacity;
        i++;
    }
}

int longestConsecutive(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    // I. Fill up the HashSet -- O(n)
    HashSet* set = setCreate(numsSize * 2);
    for (int i = 0; i < numsSize; i++) {
        setInsert(set, nums[i]);
    }

    int longestStreak = 0;

    // II. Iterate through the nums -- O(n)
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];

        // III. Check if it's a beginning -- O(1)
        if(setContains(set, num - 1)) {
            continue;
        }

        int streak = 1;

        // IV. Check values after it -- O(m)
        while(setContains(set, num + 1)) {
            num++;
            streak++;
            setRemove(set, num);
        }

        // V. Compare current streak to the longest one -- O(1)
        if (streak > longestStreak) {
            longestStreak = streak;
        }
    }

    setFree(set);
    return longestStreak;
}
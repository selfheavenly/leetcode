#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int timestamp;
    char* value;
} TimeValuePair;

typedef struct {
    char* key;
    TimeValuePair* values;
    int size;
    int capacity;
} TimeMapEntry;

typedef struct {
    TimeMapEntry* entries;
    int size;
    int capacity;
} TimeMap;


TimeMap* timeMapCreate() {
    TimeMap* obj = (TimeMap*)malloc(sizeof(TimeMap));
    obj->entries = (TimeMapEntry*)malloc(10 * sizeof(TimeMapEntry));
    obj->size = 0;
    obj->capacity = 10;
    return obj;
}

int findKey(TimeMap* obj, const char* key) {
    for (int i = 0; i < obj->size; i++) {
        if (strcmp(obj->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void resizeValues(TimeValuePair** values, int* capacity) {
    *capacity *= 2;
    *values = (TimeValuePair*)realloc(*values, (*capacity) * sizeof(TimeValuePair));
}

void timeMapSet(TimeMap* obj, char* key, char* value, int timestamp) {
    int index = findKey(obj, key);

    if (index == -1) {
        if (obj->size == obj->capacity) {
            obj->capacity *= 2;
            obj->entries = (TimeMapEntry*)realloc(obj->entries, obj->capacity * sizeof(TimeMapEntry));
        }
        obj->entries[obj->size].key = strdup(key);
        obj->entries[obj->size].values = (TimeValuePair*)malloc(10 * sizeof(TimeValuePair));
        obj->entries[obj->size].size = 0;
        obj->entries[obj->size].capacity = 10;
        index = obj->size;
        obj->size++;
    }

    TimeMapEntry* entry = &obj->entries[index];

    if (entry->size == entry->capacity) {
        resizeValues(&entry->values, &entry->capacity);
    }

    entry->values[entry->size].timestamp = timestamp;
    entry->values[entry->size].value = strdup(value);
    entry->size++;
}

char* timeMapGet(TimeMap* obj, char* key, int timestamp) {
    int index = findKey(obj, key);
    if (index == -1) {
        return "";
    }

    TimeMapEntry* entry = &obj->entries[index];

    // Binary search for the largest timestamp <= given timestamp
    int left = 0, right = entry->size - 1;
    char* result = "";
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (entry->values[mid].timestamp <= timestamp) {
            result = entry->values[mid].value;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

void timeMapFree(TimeMap* obj) {
    for (int i = 0; i < obj->size; i++) {
        free(obj->entries[i].key);
        for (int j = 0; j < obj->entries[i].size; j++) {
            free(obj->entries[i].values[j].value);
        }
        free(obj->entries[i].values);
    }
    free(obj->entries);
    free(obj);
}
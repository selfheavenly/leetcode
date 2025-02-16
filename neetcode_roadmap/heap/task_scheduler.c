#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int freq;
} Task;

void swap(Task* a, Task* b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(Task* heap, int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left].freq > heap[largest].freq) {
        largest = left;
    }
    if (right < size && heap[right].freq > heap[largest].freq) {
        largest = right;
    }
    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        heapify_down(heap, size, largest);
    }
}

void heapify_up(Task* heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap[index].freq > heap[parent].freq) {
        swap(&heap[index], &heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void insert(Task* heap, int* size, int freq) {
    heap[*size].freq = freq;
    heapify_up(heap, *size);
    (*size)++;
}

int extract_max(Task* heap, int* size) {
    if (*size == 0) return 0;
    int max_value = heap[0].freq;
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify_down(heap, *size, 0);
    return max_value;
}

int least_interval(char* tasks, int tasks_size, int n) {
    if (n == 0) return tasks_size;

    int freq[26] = {0};

    for (int i = 0; i < tasks_size; i++) {
        freq[tasks[i] - 'A']++;
    }

    int max_freq = 0, max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_count = 1;
        } else if (freq[i] == max_freq) {
            max_count++;
        }
    }

    int part_count = max_freq - 1;
    int part_length = n + 1;
    int min_intervals = part_count * part_length + max_count;

    return tasks_size > min_intervals ? tasks_size : min_intervals;
}

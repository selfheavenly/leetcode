#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* heap;
    int size;
} MaxHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(MaxHeap* maxHeap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < maxHeap->size && maxHeap->heap[left] > maxHeap->heap[largest]) {
        largest = left;
    }
    if (right < maxHeap->size && maxHeap->heap[right] > maxHeap->heap[largest]) {
        largest = right;
    }
    if (largest != index) {
        swap(&maxHeap->heap[index], &maxHeap->heap[largest]);
        heapify_down(maxHeap, largest);
    }
}

void heapify_up(MaxHeap* maxHeap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && maxHeap->heap[index] > maxHeap->heap[parent]) {
        swap(&maxHeap->heap[index], &maxHeap->heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void insert(MaxHeap* maxHeap, int val) {
    maxHeap->heap[maxHeap->size] = val;
    heapify_up(maxHeap, maxHeap->size);
    maxHeap->size++;
}

int extract_max(MaxHeap* maxHeap) {
    if (maxHeap->size == 0) return 0;
    int max_value = maxHeap->heap[0];
    maxHeap->heap[0] = maxHeap->heap[maxHeap->size - 1];
    maxHeap->size--;
    heapify_down(maxHeap, 0);
    return max_value;
}

int last_stone_weight(int* stones, int stones_size) {
    MaxHeap maxHeap;
    maxHeap.heap = (int*)malloc(stones_size * sizeof(int));
    maxHeap.size = 0;

    for (int i = 0; i < stones_size; i++) {
        insert(&maxHeap, stones[i]);
    }

    while (maxHeap.size > 1) {
        int stone1 = extract_max(&maxHeap);
        int stone2 = extract_max(&maxHeap);
        if (stone1 != stone2) {
            insert(&maxHeap, stone1 - stone2);
        }
    }

    int last_stone = (maxHeap.size == 1) ? maxHeap.heap[0] : 0;
    free(maxHeap.heap);
    return last_stone;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* heap;
    int size;
    int capacity;
} KthLargest;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(int* heap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapify_down(heap, size, smallest);
    }
}

void heapify_up(int* heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap[index] < heap[parent]) {
        swap(&heap[index], &heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* obj = (KthLargest*)malloc(sizeof(KthLargest));
    obj->heap = (int*)malloc(k * sizeof(int));
    obj->size = 0;
    obj->capacity = k;

    for (int i = 0; i < numsSize; i++) {
        if (obj->size < k) {
            obj->heap[obj->size] = nums[i];
            heapify_up(obj->heap, obj->size);
            obj->size++;
        } else if (nums[i] > obj->heap[0]) {
            obj->heap[0] = nums[i];
            heapify_down(obj->heap, k, 0);
        }
    }
    return obj;
}

int kthLargestAdd(KthLargest* obj, int val) {
    if (obj->size < obj->capacity) {
        obj->heap[obj->size] = val;
        heapify_up(obj->heap, obj->size);
        obj->size++;
    } else if (val > obj->heap[0]) {
        obj->heap[0] = val;
        heapify_down(obj->heap, obj->capacity, 0);
    }
    return obj->heap[0];
}

void kthLargestFree(KthLargest* obj) {
    free(obj->heap);
    free(obj);
}

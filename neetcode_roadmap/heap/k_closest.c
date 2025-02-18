#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    int dist;
} Point;

void swap(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(Point* heap, int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left].dist > heap[largest].dist) largest = left;
    if (right < size && heap[right].dist > heap[largest].dist) largest = right;

    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        heapify_down(heap, size, largest);
    }
}

void heapify_up(Point* heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap[index].dist > heap[parent].dist) {
        swap(&heap[index], &heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void insert_heap(Point* heap, int* size, int x, int y, int dist, int k) {
    if (*size < k) {
        heap[*size] = (Point){x, y, dist};
        heapify_up(heap, *size);
        (*size)++;
    } else if (dist < heap[0].dist) {
        heap[0] = (Point){x, y, dist};
        heapify_down(heap, *size, 0);
    }
}

int** kClosest(int** points, int pointsSize, int* pointsColSize, int k, int* returnSize, int** returnColumnSizes) {
    Point heap[k];
    int heap_size = 0;

    for (int i = 0; i < pointsSize; i++) {
        int x = points[i][0], y = points[i][1];
        int dist = x * x + y * y;
        insert_heap(heap, &heap_size, x, y, dist, k);
    }

    int** result = (int**)malloc(sizeof(int*) * k);
    *returnColumnSizes = (int*)malloc(sizeof(int) * k);
    *returnSize = k;

    for (int i = 0; i < k; i++) {
        result[i] = (int*)malloc(sizeof(int) * 2);
        result[i][0] = heap[i].x;
        result[i][1] = heap[i].y;
        (*returnColumnSizes)[i] = 2;
    }

    return result;
}

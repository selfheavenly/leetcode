#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF 1000000000

typedef struct {
    int node, weight;
} edge;

typedef struct {
    edge* edges;
    int size, capacity;
} adj_list;

typedef struct {
    int dist, node;
} heap_node;

typedef struct {
    heap_node* heap;
    int size;
} min_heap;

adj_list* graph;
int* dist;
bool* visited;

min_heap* create_heap(int capacity) {
    min_heap* h = (min_heap*)malloc(sizeof(min_heap));
    h->heap = (heap_node*)malloc(capacity * sizeof(heap_node));
    h->size = 0;
    return h;
}

void swap(heap_node* a, heap_node* b) {
    heap_node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(min_heap* h, int i) {
    int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < h->size && h->heap[left].dist < h->heap[smallest].dist) smallest = left;
    if (right < h->size && h->heap[right].dist < h->heap[smallest].dist) smallest = right;
    if (smallest != i) {
        swap(&h->heap[i], &h->heap[smallest]);
        heapify(h, smallest);
    }
}

void push_heap(min_heap* h, int node, int dist) {
    int i = h->size++;
    h->heap[i].dist = dist;
    h->heap[i].node = node;
    while (i && h->heap[i].dist < h->heap[(i - 1) / 2].dist) {
        swap(&h->heap[i], &h->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

heap_node pop_heap(min_heap* h) {
    heap_node root = h->heap[0];
    h->heap[0] = h->heap[--h->size];
    heapify(h, 0);
    return root;
}

void add_edge(int u, int v, int w) {
    graph[u].edges[graph[u].size++] = (edge){v, w};
}

void dijkstra(int n, int k) {
    min_heap* pq = create_heap(n * n);
    dist[k] = 0;
    push_heap(pq, k, 0);
    while (pq->size) {
        heap_node node = pop_heap(pq);
        int u = node.node;
        if (visited[u]) continue;
        visited[u] = true;
        for (int i = 0; i < graph[u].size; i++) {
            int v = graph[u].edges[i].node;
            int weight = graph[u].edges[i].weight;
            if (!visited[v] && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                push_heap(pq, v, dist[v]);
            }
        }
    }
    free(pq->heap);
    free(pq);
}

int network_delay_time(int times[][3], int times_size, int n, int k) {
    graph = (adj_list*)malloc((n + 1) * sizeof(adj_list));
    dist = (int*)malloc((n + 1) * sizeof(int));
    visited = (bool*)malloc((n + 1) * sizeof(bool));
    for (int i = 1; i <= n; i++) {
        graph[i].edges = (edge*)malloc(times_size * sizeof(edge));
        graph[i].size = 0;
        graph[i].capacity = times_size;
        dist[i] = INF;
        visited[i] = false;
    }
    for (int i = 0; i < times_size; i++)
        add_edge(times[i][0], times[i][1], times[i][2]);
    dijkstra(n, k);
    int max_time = 0;
    for (int i = 1; i <= n; i++)
        if (dist[i] == INF) return -1;
        else if (dist[i] > max_time) max_time = dist[i];
    for (int i = 1; i <= n; i++) free(graph[i].edges);
    free(graph);
    free(dist);
    free(visited);
    return max_time;
}


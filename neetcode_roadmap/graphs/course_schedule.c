#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list {
    int course;
    struct list *next;
} Node;

Node* push(Node* head, int course) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->course = course;
    new_node->next = head;
    return new_node;
}

bool dfs(Node** graph, int* visited, int* backtrack, int course) {
    visited[course] = 1;
    backtrack[course] = 1;

    for (Node* neighbor = graph[course]; neighbor != NULL; neighbor = neighbor->next) {
        if (!visited[neighbor->course]) {
            if (dfs(graph, visited, backtrack, neighbor->course)) {
                return true;
            }
        } else if (backtrack[neighbor->course]) {
            return true; // Cycle detected
        }
    }

    backtrack[course] = 0;
    return false;
}

bool can_finish(int num_courses, int** prerequisites, int prerequisites_size, int* prerequisites_col_size) {
    Node** graph = (Node**)calloc(num_courses, sizeof(Node*));
    int* visited = (int*)calloc(num_courses, sizeof(int));
    int* backtrack = (int*)calloc(num_courses, sizeof(int));

    for (int i = 0; i < prerequisites_size; i++) {
        int course = prerequisites[i][0];
        int prereq = prerequisites[i][1];
        graph[prereq] = push(graph[prereq], course);
    }

    for (int i = 0; i < num_courses; i++) {
        if (!visited[i] && dfs(graph, visited, backtrack, i)) {
            return false;
        }
    }

    free(visited);
    free(backtrack);
    for (int i = 0; i < num_courses; i++) {
        free(graph[i]);
    }
    free(graph);
    
    return true;
}

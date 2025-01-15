#include <stdlib.h>

struct Node {
    int val;
    struct Node* next;
    struct Node* random;
};

struct Node* createNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->val = val;
    node->next = NULL;
    node->random = NULL;
    return node;
}

struct Node* copyRandomList(struct Node* head) {
	if (!head) return NULL;

    struct Node* curr = head;
    while (curr) {
        struct Node* copy = createNode(curr->val);
        copy->next = curr->next;
        curr->next = copy;
        curr = copy->next;
    }

    curr = head;
    while (curr) {
        if (curr->random) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }

    struct Node* dummy = createNode(0);
    struct Node* copyCurr = dummy;
    curr = head;

    while (curr) {
        struct Node* copy = curr->next;
        // Unlink the copy node from the original
        curr->next = copy->next;
        copyCurr->next = copy;
        copyCurr = copy;
        curr = curr->next;
    }

    struct Node* copiedHead = dummy->next;
    free(dummy);
    return copiedHead;
}
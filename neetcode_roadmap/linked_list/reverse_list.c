#include <stdlib.h>
struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode ListNode;

struct ListNode* reverseList(struct ListNode* head){
    if(!head || !head->next) return head;
    struct ListNode* prev = head;
    struct ListNode* curr = prev->next;
    head->next = NULL;
    while(prev && curr){
        struct ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;    
}
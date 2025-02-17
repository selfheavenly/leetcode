#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 501
#define MAX_FEED_SIZE 10

typedef struct tweet {
    int tweet_id;
    int timestamp;
    struct tweet* next;
} tweet;

typedef struct {
    tweet* tweets[MAX_USERS];
    bool following[MAX_USERS][MAX_USERS];
    int timestamp;
} twitter;

twitter* twitter_create() {
    twitter* obj = (twitter*)malloc(sizeof(twitter));
    memset(obj->tweets, 0, sizeof(obj->tweets));
    memset(obj->following, false, sizeof(obj->following));
    obj->timestamp = 0;
    return obj;
}

void post_tweet(twitter* obj, int user_id, int tweet_id) {
    tweet* new_tweet = (tweet*)malloc(sizeof(tweet));
    new_tweet->tweet_id = tweet_id;
    new_tweet->timestamp = obj->timestamp++;
    new_tweet->next = obj->tweets[user_id];
    obj->tweets[user_id] = new_tweet;
}

typedef struct {
    int tweet_id;
    int timestamp;
} heap_node;

void swap(heap_node* a, heap_node* b) {
    heap_node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(heap_node* heap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < size && heap[left].timestamp < heap[smallest].timestamp) smallest = left;
    if (right < size && heap[right].timestamp < heap[smallest].timestamp) smallest = right;
    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapify_down(heap, size, smallest);
    }
}

void heapify_up(heap_node* heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap[index].timestamp < heap[parent].timestamp) {
        swap(&heap[index], &heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void insert_heap(heap_node* heap, int* size, int tweet_id, int timestamp) {
    if (*size < MAX_FEED_SIZE) {
        heap[*size].tweet_id = tweet_id;
        heap[*size].timestamp = timestamp;
        heapify_up(heap, *size);
        (*size)++;
    } else if (timestamp > heap[0].timestamp) {
        heap[0].tweet_id = tweet_id;
        heap[0].timestamp = timestamp;
        heapify_down(heap, *size, 0);
    }
}

int* get_news_feed(twitter* obj, int user_id, int* return_size) {
    heap_node min_heap[MAX_FEED_SIZE];
    int heap_size = 0;

    tweet* curr = obj->tweets[user_id];
    while (curr) {
        insert_heap(min_heap, &heap_size, curr->tweet_id, curr->timestamp);
        curr = curr->next;
    }

    for (int i = 1; i < MAX_USERS; i++) {
        if (obj->following[user_id][i]) {
            curr = obj->tweets[i];
            while (curr) {
                insert_heap(min_heap, &heap_size, curr->tweet_id, curr->timestamp);
                curr = curr->next;
            }
        }
    }

    int* result = (int*)malloc(sizeof(int) * heap_size);
    *return_size = heap_size;
    for (int i = heap_size - 1; i >= 0; i--) {
        result[i] = min_heap[0].tweet_id;
        min_heap[0] = min_heap[heap_size - 1];
        heap_size--;
        heapify_down(min_heap, heap_size, 0);
    }

    return result;
}

void follow(twitter* obj, int follower_id, int followee_id) {
    obj->following[follower_id][followee_id] = true;
}

void unfollow(twitter* obj, int follower_id, int followee_id) {
    obj->following[follower_id][followee_id] = false;
}

void twitter_free(twitter* obj) {
    for (int i = 0; i < MAX_USERS; i++) {
        tweet* curr = obj->tweets[i];
        while (curr) {
            tweet* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(obj);
}

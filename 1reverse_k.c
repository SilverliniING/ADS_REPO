// 1.	Given an integer k and a queue of integers,  reverse the order of the first k elements of the queue, leaving the other elements in the same relative order.

#include<stdio.h>
#include<stdlib.h>

struct Queue {
    struct QueueNode *front, *rear;
};

struct QueueNode {
    int data;
    struct QueueNode* next;
};

struct QueueNode* newNode(int data) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

struct Queue* initQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(struct Queue* queue, int data) {
    struct QueueNode* temp = newNode(data);

    if (queue->rear == NULL) {
        queue->front = queue->rear = temp;
        return;
    }

    queue->rear->next = temp;
    queue->rear = temp;
}

int dequeue(struct Queue* queue) {
    if (queue->front == NULL)
        return -1;

    struct QueueNode* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    free(temp);
    return data;
}

void reverse_k(struct Queue *queue, int k){
    if (queue->front == NULL || k <= 0)
        return;

    struct QueueNode* current = queue->front;
    struct QueueNode* prev = NULL;
    struct QueueNode* next = NULL;

    int index = 0;

    while (current != NULL && index < k) {
        next = current->next;

        current->next = prev;

        prev = current;
        current = next;

        index ++;
    }

    queue->front->next = current;
    queue->front = prev;
}

void print_queue(struct Queue *queue){
    struct QueueNode* temp = queue->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(){
    int k;
    struct Queue* queue = initQueue();
    enqueue(queue, 0);
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    enqueue(queue, 6);
    enqueue(queue, 7);
    enqueue(queue, 8);
    enqueue(queue, 9);

    k = 5;

    printf("Original queue: ");
    print_queue(queue);

    reverse_k(queue, k);

    printf("Reversed queue: ");
    print_queue(queue);

    return 0;
}
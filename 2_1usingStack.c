// 2.	Given a queue of integers of even length, rearrange the elements by interleaving the first half of the queue with the second half of the queue. 
//      1.	Use stack

// method followed
// Enqueue the first half of the elements into the stack.
// Dequeue the remaining elements of the queue and enqueue them back into the queue alternately with elements popped from the stack.
#include <stdio.h>
#include <stdlib.h>

struct QueueNode {
    int data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode *front, *rear;
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

void push(struct Queue* stack, int data) {
    enqueue(stack, data);
}

int pop(struct Queue* stack) {
    if (stack->front == NULL)
        return -1;

    struct QueueNode* current = stack->front;
    struct QueueNode* prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
        stack->front = stack->rear = NULL;
    else
        prev->next = NULL;

    int data = current->data;
    free(current);
    return data;
}

int size(struct Queue* queue) {
    int count = 0;
    struct QueueNode* temp = queue->front;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void interleaveQueue(struct Queue* queue) {
    int half_size = size(queue) / 2;
    if (half_size % 2 != 0)
    {
        printf("Size of queue is not even.\n");
        return;
    }
    
    struct Queue* stack = initQueue();

    for (int i = 0; i < half_size; i++) {
        push(stack, dequeue(queue));
    }

    while (stack->front != NULL) {
        enqueue(queue, pop(stack));
        enqueue(queue, dequeue(queue));
    }

    free(stack);
}

void printQueue(struct Queue* queue) {
    struct QueueNode* temp = queue->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Queue* queue = initQueue();
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    enqueue(queue, 6);
    enqueue(queue, 7);
    enqueue(queue, 8);

    printf("Original queue: ");
    printQueue(queue);

    interleaveQueue(queue);

    printf("Interleaved queue: ");
    printQueue(queue);

    return 0;
}

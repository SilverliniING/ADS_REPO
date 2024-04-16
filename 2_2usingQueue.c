#include <stdio.h>
#include <stdlib.h>

struct QueueNode {
    int data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode *front, *rear;
};

struct QueueNode* newQueueNode(int data) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(struct Queue* queue, int data) {
    struct QueueNode* temp = newQueueNode(data);

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

void printQueue(struct Queue* queue) {
    struct QueueNode* temp = queue->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void splitQueue(struct Queue* queue, struct Queue* firstHalf, struct Queue* secondHalf) {
    struct QueueNode* slowPtr = queue->front;
    struct QueueNode* fastPtr = queue->front;
    while (fastPtr != NULL && fastPtr->next != NULL) {
        enqueue(firstHalf, slowPtr->data);
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
    }

    struct QueueNode* current = slowPtr;
    while (current != NULL) {
        enqueue(secondHalf, current->data);
        current = current->next;
    }

}

void reverseQueue(struct Queue* queue) {
    struct QueueNode* prev = NULL;
    struct QueueNode* current = queue->front;
    struct QueueNode* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    queue->rear = queue->front;
    queue->front = prev;
}

void interleaveQueues(struct Queue* queue1, struct Queue* queue2) {
    struct QueueNode* current1 = queue1->front;
    struct QueueNode* current2 = queue2->front;

    while (current1 != NULL && current2 != NULL) {
        struct QueueNode* temp1 = current1->next;
        struct QueueNode* temp2 = current2->next;

        current1->next = current2;
        current2->next = temp1;

        current1 = temp1;
        current2 = temp2;
    }

    if (current2 != NULL) {
        queue1->rear = queue2->rear;
    }
}

int main() {
    struct Queue* queue = createQueue();
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

    struct Queue* firstHalf = createQueue();
    struct Queue* secondHalf = createQueue();
    splitQueue(queue, firstHalf, secondHalf);

    // reverseQueue(secondHalf);

    interleaveQueues(firstHalf, secondHalf);

    printf("Queue after interleaving: ");
    printQueue(firstHalf);

    return 0;
}
